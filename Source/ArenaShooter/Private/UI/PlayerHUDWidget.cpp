// Arena Shooter


#include "UI/PlayerHUDWidget.h"

#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "Utils/Utils.h"

float UPlayerHUDWidget::GetHealthPercent() const
{
	const UHealthComponent* HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
	if (HealthComponent == nullptr)
	{
		return 0.f;
	}

	return HealthComponent->GetHealthPercent();
}

bool UPlayerHUDWidget::IsPlayerAlive() const
{
	const UHealthComponent* HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool UPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const UWeaponComponent* WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
	if (WeaponComponent == nullptr)
	{
		return false;
	}
	
	return WeaponComponent->GetWeaponUIData(UIData);
}

bool UPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& UIData) const
{
	const UWeaponComponent* WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
	if (WeaponComponent == nullptr)
	{
		return false;
	}
	
	return WeaponComponent->GetWeaponAmmoData(UIData);
}

bool UPlayerHUDWidget::IsPlayerSpectating() const
{
	const APlayerController* const PlayerController = GetOwningPlayer();
	return PlayerController && PlayerController->GetStateName() == NAME_Spectating;
}
