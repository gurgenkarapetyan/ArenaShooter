// Arena Shooter


#include "AI/AICharacterController.h"

#include "AICharacter.h"
#include "AICharacterPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAICharacterController::AAICharacterController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAICharacterPerceptionComponent>(TEXT("AI Perception Component"));
	SetPerceptionComponent(*AIPerceptionComponent);
	AIPerceptionComponent->bEditableWhenInherited = true;

	SetAISenseConfigSightProperties();

	bWantsPlayerState = true;
}

void AAICharacterController::SetAISenseConfigSightProperties()
{
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Sense"));
	if (AISenseConfig_Sight)
	{
		AISenseConfig_Sight->SightRadius = 1000.f;
		AISenseConfig_Sight->LoseSightRadius = 1500.f;
		AISenseConfig_Sight->PeripheralVisionAngleDegrees = 60.f;
		AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
		AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
		AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = true;
		AISenseConfig_Sight->SetMaxAge(1.f);
		
		AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	}
}

void AAICharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	const AAICharacter* const AICharacter = Cast<AAICharacter>(InPawn);
	if (AICharacter)
	{
		RunBehaviorTree(AICharacter->GetBehaviorTree());
	}
}

void AAICharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AActor* const AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* AAICharacterController::GetFocusOnActor() const
{
	if (GetBlackboardComponent() == nullptr)
	{
		return nullptr;
	}

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
