// Arena Shooter


#include "AI/AICharacter.h"

#include "AIController.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();
}
