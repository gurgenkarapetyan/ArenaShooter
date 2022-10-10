// Arena Shooter


#include "Weapon/WeaponComponent.h"

#include "BaseWeapon.h"
#include "GameFramework/Character.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
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

void UWeaponComponent::Fire()
{
	if (CurrentWeapon == nullptr)
	{
		return;
	}

	CurrentWeapon->Fire();
}
