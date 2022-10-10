// Arena Shooter


#include "Player/ShooterBaseCharacter.h"

#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ShooterMovementComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"

AShooterBaseCharacter::AShooterBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UShooterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.f, 100.f, 80.f);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Health Text Component"));
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon Component"));
}

void AShooterBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &AShooterBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AShooterBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &AShooterBaseCharacter::OnGroundLanded);
}

void AShooterBaseCharacter::OnDeath()
{
	PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.f);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AShooterBaseCharacter::OnHealthChanged(float Health) const
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));	
}

void AShooterBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const float FallVelocityZ = -GetVelocity().Z;
	if (FallVelocityZ < LandedDamageVelocity.X)
	{
		return;
	}
	
	const float FallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	TakeDamage(FallDamage, FPointDamageEvent{}, nullptr, nullptr);
}


void AShooterBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterBaseCharacter::MoveForward);	
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AShooterBaseCharacter::Turn);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AShooterBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AShooterBaseCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UWeaponComponent::Fire);
}

void AShooterBaseCharacter::MoveForward(const float Value)
{
	IsMovingForward = Value > 0.f;

	if (Value == 0.f)
	{
		return; 
	}
	
	AddMovementInput(GetActorForwardVector(), Value);
}

void AShooterBaseCharacter::MoveRight(const float Value)
{
	if (Value == 0.f)
	{
		return; 
	}
	
	AddMovementInput(GetActorRightVector(), Value);
}

void AShooterBaseCharacter::LookUp(const float Value)
{
	AddControllerPitchInput(Value);
}

void AShooterBaseCharacter::Turn(const float Value)
{
	AddControllerYawInput(Value);
}

void AShooterBaseCharacter::OnStartRunning()
{
	IsRunPressed = true;
}

void AShooterBaseCharacter::OnStopRunning()
{
	IsRunPressed = false;
}

float AShooterBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
	{
		return 0.f;
	}
	
	const FVector VelocityNormal = GetVelocity().GetSafeNormal();
	const float AngelBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	const float Degrees = FMath::RadiansToDegrees(AngelBetween);
	
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}
