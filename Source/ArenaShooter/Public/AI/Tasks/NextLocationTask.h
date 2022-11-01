// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API UNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UNextLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float Radius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FBlackboardKeySelector AimLocationKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	bool bSelfCenter = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (EditCondition = "!bSelfCenter"))
	FBlackboardKeySelector CenterActorKey;
};
