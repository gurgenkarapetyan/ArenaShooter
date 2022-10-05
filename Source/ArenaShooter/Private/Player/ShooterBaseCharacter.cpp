// Arena Shooter


#include "Player/ShooterBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/ShooterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AShooterBaseCharacter::AShooterBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UShooterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AShooterBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterBaseCharacter::MoveForward);	
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AShooterBaseCharacter::Turn);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AShooterBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AShooterBaseCharacter::OnStopRunning);
}

void AShooterBaseCharacter::MoveForward(const float Value)
{
	IsMovingForward = Value > 0.f;
	AddMovementInput(GetActorForwardVector(), Value);
}

void AShooterBaseCharacter::MoveRight(const float Value)
{
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
