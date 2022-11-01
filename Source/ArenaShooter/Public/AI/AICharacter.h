// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "Player/ShooterBaseCharacter.h"
#include "AICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class ARENASHOOTER_API AAICharacter : public AShooterBaseCharacter
{
	GENERATED_BODY()

public:
	AAICharacter(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
};
