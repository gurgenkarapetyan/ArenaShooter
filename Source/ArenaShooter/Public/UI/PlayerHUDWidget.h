// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "ArenaShooter/Public/CoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

UCLASS()
class ARENASHOOTER_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Get health in percentage from widget owning character HealthComponent. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	/** Get weapon UI data from widget owning character WeaponComponent. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
	
	/** Get weapon UI data from widget owning character WeaponComponent. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& UIData) const;

	/** If Player alive we are displaying player related HUD. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	/** If Player died and is in spectator mode hide player related HUD and display spectator HUD. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

	virtual bool Initialize() override;

	/**  */
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();
	
private:
	void OnHealthChanged(float Health, float HealthDelta);
};
