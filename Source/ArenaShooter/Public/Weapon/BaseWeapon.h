// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All)

UCLASS()
class ARENASHOOTER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

	virtual void Fire();
	
protected:
	virtual void BeginPlay() override;

	APlayerController* GetPlayerController() const;

	/** Send bullet and check if it hits something. */
	void MakeShot() ;

	/** Get related data for line trace to draw.
	 * @param TraceStart start point location of the line trace to draw.
	 * @param TraceEnd end point location of the line trace to draw.
	 */
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	/** Get Character's camera view point location.
	 *	@param ViewLocation Character's camera location
	 *	@param ViewRotation Character's camera rotation
	 */
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const; 
	
	/** Draw line trace from the Character camera view point.
	 *	@param HitResult related information of the line trace.
	 *	@param TraceStart start point location of the line trace.
	 *	@param TraceEnd end point location of the line trace.
	 */
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const; 

	/** Get World location of Weapon's Skeletal Mesh muzzle socket. */
	FVector GetMuzzleWorldLocation() const;

	/** Apply damage to the Character.
	 * @param HitResult related information of line trace after hit.
	 */
	void MakeDamage(const FHitResult& HitResult);
	
protected:
	/** Skeletal Mesh for the Weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMeshComponent;

	/** Muzzle socket name in Weapon Skeleton Mesh. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	FName MuzzleSocketName = "MuzzleSocket";

	/** Maximum length of line trace to reach. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TraceMaxDistance = 1500.f;

	/** Amount of damage to apply when bullet hits Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DamagedAmount = 10.f;
};
