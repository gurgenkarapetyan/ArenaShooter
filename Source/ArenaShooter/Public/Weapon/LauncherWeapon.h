// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "LauncherWeapon.generated.h"

class AProjectile;

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API ALauncherWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	virtual void MakeShot() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AProjectile> ProjectileClass;
};
