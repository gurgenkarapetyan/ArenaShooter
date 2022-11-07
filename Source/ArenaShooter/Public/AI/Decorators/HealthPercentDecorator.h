// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "HealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API UHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UHealthPercentDecorator();
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float HealthPercent = 0.6f;
};
