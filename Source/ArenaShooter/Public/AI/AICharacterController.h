// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICharacterController.generated.h"

class UAICharacterPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class ARENASHOOTER_API AAICharacterController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAICharacterController();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;
	
private:
	/** Set Perception Component Sense Config Sight Properties*/
	void SetAISenseConfigSightProperties();

	AActor* GetFocusOnActor() const;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAICharacterPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Perception")
	UAISenseConfig_Sight* AISenseConfig_Sight = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";
};
