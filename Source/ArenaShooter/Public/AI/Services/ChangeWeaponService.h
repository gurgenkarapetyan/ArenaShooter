// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API UChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
	UChangeWeaponService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Probability = 0.5;
};
