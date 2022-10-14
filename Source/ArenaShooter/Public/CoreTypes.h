#pragma once

#include "CoreTypes.generated.h"

class ABaseWeapon;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	/** Number of bullets that weapons has in the clip. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	int32 Bullets;

	/** Number of clips. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (EditCondition = "!Infinite"))
	int32 Clips;

	/** If weapon has an infinite number of clips. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	/**  Weapon class blueprint. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABaseWeapon> WeaponClass;
	
	/**  Based on weapon type reload anim montage. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;
};