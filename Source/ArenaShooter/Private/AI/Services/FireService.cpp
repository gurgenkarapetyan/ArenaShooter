// Arena Shooter


#include "AI/Services/FireService.h"

#include "AIController.h"
#include "WeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Utils/Utils.h"

UFireService::UFireService()
{
	NodeName = "Fire";
}

void UFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController* const AIController = OwnerComp.GetAIOwner();
	const UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();

	const bool bHasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	if (AIController)
	{
		UWeaponComponent* WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(AIController->GetPawn());
		if (WeaponComponent)
		{
			bHasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
