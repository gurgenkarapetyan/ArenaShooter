// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASHOOTER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	/** Called when the fire button is pressed/released. */
	void StartFire();
	void StopFire();
	
protected:
	virtual void BeginPlay() override;

	/** Spawn Weapon at the Character's hand. */
	void SpawnWeapon();

protected:
	/** Set this in Blueprints for the Character Weapon class. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ABaseWeapon> WeaponClass;

	/** Name of the socket where the weapon will be attached. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

private:
	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;
};
