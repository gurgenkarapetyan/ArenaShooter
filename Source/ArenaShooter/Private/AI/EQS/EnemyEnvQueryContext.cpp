// Arena Shooter


#include "AI/EQS/EnemyEnvQueryContext.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	AActor* const QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	const UBlackboardComponent* const Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if (Blackboard == nullptr)
	{
		return;
	}

	UObject* const ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName);
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));	
}
