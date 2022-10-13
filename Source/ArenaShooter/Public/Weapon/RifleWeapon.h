// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "RifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API ARifleWeapon : public ABaseWeapon 
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void MakeShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;


	/** Apply damage to the Character.
	 * @param HitResult related information of line trace after hit.
	 */
	void MakeDamage(const FHitResult& HitResult);
	
protected:
	/** Time between shots during automatic fire. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;

	/** Bullet deviation during fire. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpread = 1.5f;
	
private:
	/** Time handler for automatic fire. */
	FTimerHandle ShotTimerHandle;
};
