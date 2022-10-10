// Arena Shooter


#include "Weapon/BaseWeapon.h"

#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(WeaponMeshComponent);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseWeapon::Fire()
{
	MakeShot();
}

void ABaseWeapon::MakeShot() 
{
	if (!GetWorld())
	{
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	
	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.f);
	}
}

bool ABaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}
	
	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return true;
}

bool ABaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const APlayerController* const PlayerController = GetPlayerController();
	if (PlayerController == nullptr)
	{
		return false;
	}

	PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

APlayerController* ABaseWeapon::GetPlayerController() const
{
	const ACharacter* const Player = Cast<ACharacter>(GetOwner());
	if (Player == nullptr)
	{
		return nullptr;
	}

	return Player->GetController<APlayerController>();
}

void ABaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
	if (!GetWorld())
	{
		return;
	}
	
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
}

FVector ABaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
}

void ABaseWeapon::MakeDamage(const FHitResult& HitResult)
{
	AActor* const DamagedActor = HitResult.GetActor();
	if (DamagedActor == nullptr)
	{
		return;
	}

	DamagedActor->TakeDamage(DamagedAmount, FDamageEvent(), GetPlayerController(), this);
}
