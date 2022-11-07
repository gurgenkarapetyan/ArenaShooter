// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

class USphereComponent;

UCLASS()
class ARENASHOOTER_API ABasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePickUp();
	
	virtual void Tick(float DeltaTime) override;

	bool CouldBeTaken() const;
	
protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/** Called when the Player overlaps with pickable item . */
	virtual bool GivePickUpTo(APawn* PlayerPawn) PURE_VIRTUAL(ABasePickUp::GivePickUpTo, return false;); 
	
private:
	/** When PickUp was taken hide visibility and respawn again after specific time. */
	void PickUpWasTaken();

	/** Handle PickUp respawn after specific time. */
	void Respawn();

	void GenerateRotationYaw();
	
protected:
	/** Item Collision Component for triggering overlap events. */
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

	/** Amount of time to respawn picked item again. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	float RespawnTime = 5.f;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	bool bCouldBeTaken = true;
	
private:
	FTimerHandle RespawnTimerHandle;
	
	float RotationYaw = 0.f;
};
