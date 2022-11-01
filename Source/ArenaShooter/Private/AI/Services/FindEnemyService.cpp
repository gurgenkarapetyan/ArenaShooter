// Arena Shooter


#include "AI/Services/FindEnemyService.h"

#include "AICharacterPerceptionComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindEnemyService::UFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const AAIController* const AIController = OwnerComp.GetAIOwner();
		const UAICharacterPerceptionComponent* const PerceptionComponent = Cast<UAICharacterPerceptionComponent>(AIController->GetComponentByClass(UAICharacterPerceptionComponent::StaticClass()));
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
