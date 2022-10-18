// Arena Shooter


#include "PickUps/AmmoPickUp.h"

#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "Utils/Utils.h"

bool AAmmoPickUp::GivePickUpTo(APawn* PlayerPawn)
{
	const UHealthComponent* HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead())
	{
		return false;
	}
	
	UWeaponComponent* WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(PlayerPawn);
	if (WeaponComponent == nullptr)
	{
		return false;
	}

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
