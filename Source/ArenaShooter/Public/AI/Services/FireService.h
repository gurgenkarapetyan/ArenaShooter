// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FireService.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API UFireService : public UBTService
{
	GENERATED_BODY()
	UFireService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;
};
