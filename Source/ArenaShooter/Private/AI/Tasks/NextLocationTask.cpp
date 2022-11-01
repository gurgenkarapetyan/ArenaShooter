// Arena Shooter


#include "AI/Tasks/NextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UNextLocationTask::UNextLocationTask()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type UNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	const AAIController* const AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* const BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (AIController == nullptr || BlackboardComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* const Pawn = AIController->GetPawn();
	if (Pawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	const UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(Pawn);
	if (NavigationSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	FNavLocation NavigationLocation;
	FVector Location = Pawn->GetActorLocation();
	if (!bSelfCenter)
	{
		const AActor* const CenterActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if (CenterActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		Location = CenterActor->GetActorLocation();
	}
	
	const bool Found = NavigationSystem->GetRandomReachablePointInRadius(Location, Radius, NavigationLocation);
	if (!Found)
	{
		return EBTNodeResult::Failed;
	}
	
	BlackboardComponent->SetValueAsVector(AimLocationKey.SelectedKeyName, NavigationLocation.Location);
	return EBTNodeResult::Succeeded;
}
