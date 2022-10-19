// Arena Shooter


#include "Weapon/RifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "Components/WeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ARifleWeapon::ARifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<UWeaponFXComponent>(TEXT("Weapon FX Component"));
}

void ARifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}

void ARifleWeapon::StartFire()
{
	InitMuzzleFX();
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShot, TimeBetweenShots, true);
}

void ARifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetMuzzleFXVisibility(false);
}

void ARifleWeapon::InitMuzzleFX()
{
	if (MuzzleFXComponent == nullptr)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	SetMuzzleFXVisibility(true);
}

void ARifleWeapon::SetMuzzleFXVisibility(const bool bVisible) const
{
	if (MuzzleFXComponent )
	{
		MuzzleFXComponent->SetPaused(!bVisible);
		MuzzleFXComponent->SetVisibility(bVisible, true);
	}
}


void ARifleWeapon::MakeShot() 
{
	if (!GetWorld() || IsAmmoEmpty())
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
	
	FVector TraceFXEnd = TraceEnd;
	if (HitResult.bBlockingHit)
	{
		// DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.f);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
		
		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}

	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
	DecreaseAmmo();
}

bool ARifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}
	
	TraceStart = ViewLocation;
	const float HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return true;
}

void ARifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	AActor* const DamagedActor = HitResult.GetActor();
	if (DamagedActor == nullptr)
	{
		return;
	}

	DamagedActor->TakeDamage(DamagedAmount, FDamageEvent(), GetPlayerController(), this);
}

void ARifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) const
{
	UNiagaraComponent* const TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	if (TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}
