// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API UFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UFindEnemyService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;
};
