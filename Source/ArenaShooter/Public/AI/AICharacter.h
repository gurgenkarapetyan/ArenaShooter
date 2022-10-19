// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "Player/ShooterBaseCharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API AAICharacter : public AShooterBaseCharacter
{
	GENERATED_BODY()

public:
	AAICharacter(const FObjectInitializer& ObjectInitializer);
};
