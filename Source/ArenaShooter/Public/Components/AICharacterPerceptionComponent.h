// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "AICharacterPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API UAICharacterPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	/** Get and return closest enemy in sight perception. */
	AActor* GetClosestEnemy() const;

private:
	/** Find the best match perceived actor and return.
	 *	@param PerceivedActors all perceived actor by AI sight perception.
	 */
	AActor* FindBestMatch(const TArray<AActor*> PerceivedActors) const;
	
	APawn* GetAIPawn() const;
};

