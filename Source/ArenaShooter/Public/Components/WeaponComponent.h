// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

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

	/** Init and subscribe to equip finished anim notify. */
	void InitAnimations();

	/** Handle when equip finished anim notify event is triggered.
	 * @param MeshComponent Character that triggered event.
	 */
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	ACharacter* GetWeaponOwner() const;

protected:
	/** Array of weapons that will be in Characters inventory. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ABaseWeapon>> WeaponClasses;

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
};
