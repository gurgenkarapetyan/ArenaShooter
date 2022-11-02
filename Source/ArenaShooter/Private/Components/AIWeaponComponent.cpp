// Arena Shooter


#include "Components/AIWeaponComponent.h"

#include "BaseWeapon.h"

void UAIWeaponComponent::StartFire()
{
	Super::StartFire();
	if (!CanFire())
	{
		return;
	}

	if (CurrentWeapon->IsAmmoEmpty())
	{
		SwitchWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void UAIWeaponComponent::SwitchWeapon()
{
	Super::SwitchWeapon();

	if (!CanEquip())
	{
		return;
	}

	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	while (NextIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty())
		{
			break;
		}
		NextIndex = (NextIndex + 1) % Weapons.Num();
	}

	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}
