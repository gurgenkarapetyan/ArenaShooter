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
	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE bool IsDead() const { return FMath::IsNearlyZero(Health); }

	/** Convert health into percentage for displaying in Health UMG. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE float GetHealthPercent() const { return Health / MaxHealth; }

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

	/** Refill Character health. */
	void HealUpdate();

	/** Set Character new Health and broadcast changes. */
	void SetHealth(float NewHealth);
	
public:
	/** Delegate for broadcast when Character is dies. */
	FOnDeath OnDeath;

	/** Delegate for broadcast when Character health changes. */
	FOnHealtChanged OnHealthChanged;
	
protected:
	/** Maximum health. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000."))
	float MaxHealth = 100.f;

	/** Refill Character health after certain amount of time. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool bAutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealUpdateTime = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealModifier = 5.0f;
	
private:
	/** Current health. */
	float Health = 0.f;

	/** Heal time handler. */
	FTimerHandle HealTimerHandle;
};
