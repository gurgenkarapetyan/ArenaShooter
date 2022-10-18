// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "ArenaShooter/Public/CoreTypes.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASHOOTER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	/** Called when the fire button is pressed/released. */
	void StartFire();
	void StopFire();

	/** Called when switching weapons. */
	void SwitchWeapon();

	/** Called when reloading weapon. */
	void Reload();

	/** If current weapon is set return weapon UI data
	 * @param UIData struct holding current weapon data. 
	 */
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	/** If current weapon is set return weapon ammo data.
	 *	@param AmmoData struct holding current weapon ammo data.
	 */
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

	
	/** Try to fill weapon with Clips and Bullets.
	 * @param WeaponType weapon type we need to add ammunition. 
	 * @param ClipsAmount number of clips to fill weapon with.
	 */
	bool TryToAddAmmo(const TSubclassOf<ABaseWeapon>WeaponType, const int32 ClipsAmount);
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	/** Spawn Weapons that the Character has in the inventory.. */
	void SpawnWeapons();

private:
	/** Attach weapon to the Character's given socket
	 *  @param Weapon that we want to attach.
	 *  @param SceneComponent Character Mesh where it will be attached to.
	 *  @param SocketName where weapon will be attached.
	 */
	void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	/** Equip with given index weapon.
	 * @param WeaponIndex that we want to be equipped with.
	 */
	void EquipWeapon(int32 WeaponIndex);

	/** Play animation montage.
	 * @param Animation to play. 
	 */
	void PlayAnimMontage(UAnimMontage* Animation) const;

	/** Init and subscribe to anim notifies. */
	void InitAnimations();

	/** Handle when equip finished anim notify event is triggered.
	 * @param MeshComponent Character that triggered event.
	 */
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	/** Handle when reload finished anim notify event is triggered.
	 * @param MeshComponent Character that triggered event.
	 */
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
	
	ACharacter* GetWeaponOwner() const;

	/** Check if weapon can fire or any animation is currently playing. */
	bool CanFire() const;

	/** Check if can equip or any animation is currently playing. */
	bool CanEquip() const;

	/** Check if can reload or any animation is currently playing. */
	bool CanReload() const;

	/** When clip is empty trigger delegate to automatically switch the clip.
	 * @param AmmoEmptyWeapon weapon that we need to reload.
	 */
	void OnEmptyClip(ABaseWeapon* AmmoEmptyWeapon);

	/** Change the clip when reload button is pressed. */
	void ChangeClip();
	
protected:
	/** Array of weapons that will be in Characters inventory. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	/** Name of the socket where the weapon will be attached to the Character's hand. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	/** Name of the socket where the weapon will be to the Character's back. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	/** Montage for Equip animations. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* EquipAnimMontage;

private:
	/** Currently equipped weapon. */
	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;

	/** Array of weapons that the Character has in the inventory. */
	TArray<ABaseWeapon*> Weapons;

	/** Current weapon index that we are equipped with. */
	int32 CurrentWeaponIndex = 0;

	/** Based on weapon type set current reload montage. */
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	/** If currently equip anim montage is playing any other action must be prevented. */
	bool bEquipAnimInProgress = false;

	/** If currently reload anim montage is playing any other action must be prevented. */
	bool bReloadAnimInProgress = false;
};
