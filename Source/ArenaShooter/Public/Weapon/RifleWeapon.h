// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "RifleWeapon.generated.h"

class UWeaponFXComponent;
class UNiagaraComponent;

UCLASS()
class ARENASHOOTER_API ARifleWeapon : public ABaseWeapon 
{
	GENERATED_BODY()

public:
	ARifleWeapon();

	virtual void BeginPlay() override;
	
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void MakeShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;


	/** Apply damage to the Character.
	 * @param HitResult related information of line trace after hit.
	 */
	void MakeDamage(const FHitResult& HitResult);

private:
	/** Spawn Niagara system and set visibility to true. */
	void InitMuzzleFX();

	/** Handle Niagara Muzzle visibility.
	 * @param bVisible 
	 */
	void SetMuzzleFXVisibility(bool bVisible) const;

	/** Spawn Niagara trace FX.
	 *	@param TraceStart start point of the trace to be spawned.
	 *	@param TraceEnd end point of the trace.
	 */
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) const;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "VFX")
	UWeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "VFX")
	FString TraceTargetName = "TraceTarget";
	
	/** Time between shots during automatic fire. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Weapon")
	float TimeBetweenShots = 0.1f;

	/** Bullet deviation during fire. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Weapon")
	float BulletSpread = 1.5f;
	
private:
	/** Time handler for automatic fire. */
	FTimerHandle ShotTimerHandle;

	/** Muzzle Niagara FX Component. */
	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;
};
