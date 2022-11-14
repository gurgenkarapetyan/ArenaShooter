#pragma once

#include "CoreTypes.generated.h"

class ABaseWeapon;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	/** Number of bullets that weapons has in the clip. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	int32 Bullets;

	/** Number of clips. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (EditCondition = "!Infinite"))
	int32 Clips;

	/** If weapon has an infinite number of clips. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	/**  Weapon class blueprint. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ABaseWeapon> WeaponClass;
	
	/**  Based on weapon type reload anim montage. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;
};


USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	/** Weapon image icon based on weapon type. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UTexture2D* MainIcon;
	
	/** Weapon crosshair icon based on weapon type. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UTexture2D* CrosshairIcon;
};

// VFX 

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	/** Decal Material. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	UMaterialInterface* Material;
	
	/** Decal Size. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	FVector Size = FVector(10.f);

	/** Life time of decal before destroy. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	float LifeTime = 5.f;

	/** Animation time for alpha component of decal */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	UNiagaraSystem* NiagaraEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	FDecalData DecalData;
};

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	/** Number of players to be spawned in game. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
	int32 PlayersNum = 2;

	/** Number of round in game. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 RoundsNum = 4;

	/** Time for each round to last. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
	int32 RoundTime = 10;

	/** Default team color if not set. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
	FLinearColor DefaultTeamColor = FLinearColor::Red;

	/** Array of colors for players base on their team ID. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
	TArray<FLinearColor> TeamColors;
};