// Arena Shooter


#include "Components/AICharacterPerceptionComponent.h"

#include "AIController.h"
#include "HealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Utils/Utils.h"

AActor* UAICharacterPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
	if (PerceivedActors.Num() == 0)
	{
		return nullptr;
	}
	
	const APawn* const AIPawn = GetAIPawn();
	
	return FindBestMatch(PerceivedActors);
}

AActor* UAICharacterPerceptionComponent::FindBestMatch(const TArray<AActor*> PerceivedActors) const
{
	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PerceivedActor: PerceivedActors)
	{
		const UHealthComponent* const HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(PerceivedActor);
		if (HealthComponent && !HealthComponent->IsDead())
		{
			const float CurrentDistance = (PerceivedActor->GetActorLocation() - GetAIPawn()->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PerceivedActor;
			}
		}
	}

	return BestPawn;
}

APawn* UAICharacterPerceptionComponent::GetAIPawn() const
{
	const AAIController* const AIController = Cast<AAIController>(GetOwner());
	if (AIController == nullptr)
	{
		return nullptr;
	}
	
	APawn* Pawn = AIController->GetPawn();
	if (Pawn == nullptr)
	{
		return nullptr;
	}

	return Pawn;
}
