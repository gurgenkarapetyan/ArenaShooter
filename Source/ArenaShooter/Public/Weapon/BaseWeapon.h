// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "ArenaShooter/Public/CoreTypes.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All)

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ABaseWeapon*);

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class ARENASHOOTER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();
	
	/** Called when the fire button is pressed/released. */
	virtual void StartFire() PURE_VIRTUAL(ABaseWeapon::StartFire);
	virtual void StopFire() {};

	/** Get UIData data struct. */
	FORCEINLINE FWeaponUIData GetUIData() const { return UIData; }

	/** Get weapon current ammo data struct. */
	FORCEINLINE FAmmoData GetAmmoData() const { return CurrentAmmoData; }
	
	/** Handle weapon clip change functionality. */
	void ChangeClip();

	bool CanReload() const;

	/** Try to fill weapon with Clips and Bullets.
	 * @param ClipsAmount number of clips to fill weapon with.
	 */
	bool TryToAddAmmo(const int32 ClipsAmount);

	/** Check if any bullet/clip is left. */
	bool IsAmmoEmpty() const;

	/** Check if Clips and Bullets are full. */
	bool IsAmmoFull() const;
	
protected:
	virtual void BeginPlay() override;

	APlayerController* GetPlayerController() const;

	/** Send bullet and check if it hits something. */
	virtual void MakeShot() PURE_VIRTUAL(ABaseWeapon::MakeShot);

	/** Get related data for line trace to draw.
	 * @param TraceStart start point location of the line trace to draw.
	 * @param TraceEnd end point location of the line trace to draw.
	 */
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

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

	/** Decrease bullets from clip when firing. */
	void DecreaseAmmo();

	/** Check if bullets in clip are empty. */
	bool IsClipEmpty() const;
	
	/** Helper function for outputting information about weapon when firing. */
	void LogAmmo() const;

	/** Create Niagara muzzle effect. */
	UNiagaraComponent* SpawnMuzzleFX() const;
	
public:
	/** Delegate for automatically changing the clip when all ammo is used. */
	FOnClipEmptySignature OnClipEmptySignature;
	
protected:
	/** Skeletal Mesh for the Weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* WeaponMeshComponent;

	/** Muzzle socket name in Weapon Skeleton Mesh. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	/** Maximum length of line trace to reach. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float TraceMaxDistance = 1500.f;

	/** Amount of damage to apply when bullet hits Character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float DamagedAmount = 10.f;

	/** Struct data for storing default information about weapon. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FAmmoData DefaultAmmoData { 15, 10, false };

	/** Struct data for storing default UI information about weapon. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	FWeaponUIData UIData;

	/** Muzzle Niagara VFX*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	UNiagaraSystem* MuzzleFX;
	
private:
	/** Struct data for storing related information about weapon. */
	FAmmoData CurrentAmmoData;
};
