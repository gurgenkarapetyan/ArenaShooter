// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "PickUps/BasePickUp.h"
#include "HealthPickUp.generated.h"


UCLASS()
class ARENASHOOTER_API AHealthPickUp : public ABasePickUp
{
	GENERATED_BODY()

protected:
	virtual bool GivePickUpTo(APawn* PlayerPawn) override;

	/** Amount of health to add to Character when item is picked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	float HealthAmount = 100.f;
};
