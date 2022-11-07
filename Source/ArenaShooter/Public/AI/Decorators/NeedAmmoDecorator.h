// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "NeedAmmoDecorator.generated.h"

class ABaseWeapon;

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API UNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UNeedAmmoDecorator();
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TSubclassOf<ABaseWeapon> WeaponType;
};
