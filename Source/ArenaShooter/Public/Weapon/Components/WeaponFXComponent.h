// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "ArenaShooter/Public/CoreTypes.h"
#include "Components/ActorComponent.h"
#include "WeaponFXComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASHOOTER_API UWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponFXComponent();

	void PlayImpactFX(const FHitResult& HitResult) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
