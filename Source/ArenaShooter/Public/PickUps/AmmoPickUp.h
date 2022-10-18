// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "PickUps/BasePickUp.h"
#include "AmmoPickUp.generated.h"

class ABaseWeapon;

UCLASS()
class ARENASHOOTER_API AAmmoPickUp : public ABasePickUp
{
	GENERATED_BODY()

protected:
	virtual bool GivePickUpTo(APawn* PlayerPawn) override;

	/** Number of clips to add to the weapon when item is picked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmount = 10.f;

	/** Type of weapon we want to add ammunition when item is picked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	TSubclassOf<ABaseWeapon> WeaponType;
};
