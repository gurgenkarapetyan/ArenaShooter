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
	check(WeaponMeshComponent);
	checkf(DefaultAmmoData.Bullets > 0, TEXT("Bullets count can't be less or equal zero"));
	checkf(DefaultAmmoData.Clips > 0, TEXT("Clips count can't be less or equal zero"));
	
	CurrentAmmoData = DefaultAmmoData;
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

void ABaseWeapon::DecreaseAmmo()
{
	if (CurrentAmmoData.Bullets == 0)
	{
		UE_LOG(BaseWeaponLog, Warning, TEXT("Clip is empty."));
		return;
	}
	
	CurrentAmmoData.Bullets--;
	LogAmmo();

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		OnClipEmptySignature.Broadcast();
	}
}

bool ABaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmoData.Infinite && CurrentAmmoData.Clips == 0 && IsClipEmpty();
}

bool ABaseWeapon::IsClipEmpty() const
{
	return CurrentAmmoData.Bullets == 0;
}

void ABaseWeapon::ChangeClip()
{
	if (!CurrentAmmoData.Infinite)
	{
		if (CurrentAmmoData.Clips == 0)
		{
			UE_LOG(BaseWeaponLog, Warning, TEXT("No More Clips"));
			return;
		}
		CurrentAmmoData.Clips--;
	}

	CurrentAmmoData.Bullets = DefaultAmmoData.Bullets;
	UE_LOG(LogTemp, Warning, TEXT("------------- Change Clip -------------"));
}

bool ABaseWeapon::CanReload() const
{
	return CurrentAmmoData.Bullets < DefaultAmmoData.Bullets && CurrentAmmoData.Clips > 0;
}

void ABaseWeapon::LogAmmo() const
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmoData.Bullets) + " / ";
	AmmoInfo += CurrentAmmoData.Infinite ? "Infinite" : FString::FromInt(CurrentAmmoData.Clips);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *AmmoInfo);
}
