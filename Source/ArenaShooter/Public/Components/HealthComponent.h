// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealtChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	/** Return Character current health. */
	FORCEINLINE float GetHealth() const { return Health; }

	/** If Health < 0.f, change Character state to dead. */
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return Health <= 0.f; }

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

public:
	/** Delegate for broadcast when Character is dies. */
	FOnDeath OnDeath;

	/** Delegate for broadcast when Character health changes. */
	FOnHealtChanged OnHealthChanged;
	
protected:
	/** Maximum health. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000."))
	float MaxHealth = 100.f;
	
private:
	/** Current health. */
	float Health = 0.f;
};
