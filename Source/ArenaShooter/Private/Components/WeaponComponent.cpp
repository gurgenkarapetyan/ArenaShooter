// Arena Shooter


#include "Components/WeaponComponent.h"

#include "BaseWeapon.h"
#include "GameFramework/Character.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UWeaponComponent::SpawnWeapon()
{
	if (!GetWorld())
	{
		return;
	}
	const ACharacter* const Character = Cast<ACharacter>(GetOwner());
	if (Character == nullptr)
	{
		return;
	}
	
	CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
	if (CurrentWeapon == nullptr)
	{
		return;
	}
	
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(GetOwner());
}

void UWeaponComponent::StartFire()
{
	if (CurrentWeapon == nullptr)
	{
		return;
	}

	CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFire()
{
	if (CurrentWeapon == nullptr)
	{
		return;
	}

	CurrentWeapon->StopFire();
}
