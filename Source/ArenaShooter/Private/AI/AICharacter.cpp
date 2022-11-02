// Arena Shooter


#include "AI/AICharacter.h"

#include "AIController.h"
#include "AIWeaponComponent.h"
#include "BrainComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UAIWeaponComponent>("Weapon Component"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
	}
}

void AAICharacter::OnDeath()
{
	Super::OnDeath();
	
	const AAIController* const AIController = Cast<AAIController>(Controller);
	if (AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->Cleanup();
	}
}
