// Arena Shooter


#include "AI/Decorators/HealthPercentDecorator.h"

#include "AIController.h"
#include "HealthComponent.h"
#include "Utils/Utils.h"

UHealthPercentDecorator::UHealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool UHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	const AAIController* const AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return false;
	}
	
	const UHealthComponent* const HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(AIController->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead())
	{
		return false;
	}
	
	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
