// Arena Shooter


#include "Components/WeaponComponent.h"

#include "AnimUtils.h"
#include "BaseWeapon.h"
#include "EquipFinishedAnimNotify.h"
#include "ReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"

constexpr static int32 WeaponNum = 2;

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData.Num() == WeaponNum, TEXT("Our Character can hold only %i weapon items"), WeaponNum);
	
	CurrentWeaponIndex = 0;
	
	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::SpawnWeapons()
{
	ACharacter* const Character = GetWeaponOwner();;
	
	if (!GetWorld())
	{
		return;
	}
	
	for (FWeaponData OneWeaponData : WeaponData)
	{
		ABaseWeapon* Weapon = GetWorld()->SpawnActor<ABaseWeapon>(OneWeaponData.WeaponClass);
		if (Weapon == nullptr)
		{
			continue;
		}

		Weapon->OnClipEmptySignature.AddUObject(this, &UWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void UWeaponComponent::OnEmptyClip(ABaseWeapon* AmmoEmptyWeapon)
{
	if (CurrentWeapon == AmmoEmptyWeapon)
	{
		ChangeClip();
	}
	else
	{
		for (const auto Weapon : Weapons)
		{
			if (Weapon == AmmoEmptyWeapon)
			{
				Weapon->ChangeClip();
			}
		}
	}
}

void UWeaponComponent::ChangeClip()
{
	if (!CanReload())
	{
		return;
	}

	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	
	bReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);	
}

bool UWeaponComponent::CanReload() const
{
	return CurrentWeapon && !bEquipAnimInProgress && !bReloadAnimInProgress && CurrentWeapon->CanReload();
}

void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent)
	{
		return;
	}
	
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UWeaponComponent::EquipWeapon(const int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid weapon index"));
		return;
	}
	
	const ACharacter* const Character = GetWeaponOwner();

	if (CurrentWeapon)
	{
		StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}
	
	CurrentWeapon = Weapons[WeaponIndex];
	CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;

	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) { return Data.WeaponClass == CurrentWeapon->GetClass(); });
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
	
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);

	bEquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) const
{
	ACharacter* const Character = GetWeaponOwner();

	Character->PlayAnimMontage(Animation);
}

void UWeaponComponent::InitAnimations()
{
	UEquipFinishedAnimNotify* EquipFinishedNotify = AnimUtils::FindNotifyByClass<UEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
		checkNoEntry();
	}

	for (const FWeaponData OneWeaponData : WeaponData)
	{
		UReloadFinishedAnimNotify* ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));
			checkNoEntry();
		}
		
		ReloadFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnReloadFinished);
	}
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	const ACharacter* const Character = GetWeaponOwner();
	
	if (Character->GetMesh() != MeshComponent)
	{
		return;
	}
	
	bEquipAnimInProgress = false;
}

void UWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	const ACharacter* const Character = GetWeaponOwner();
	
	if (Character->GetMesh() != MeshComponent)
	{
		return;
	}
	
	bReloadAnimInProgress = false;
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (const auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}

	Weapons.Empty();
	
	Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::StartFire()
{
	if (!CanFire())
	{
		return;
	}

	CurrentWeapon->StartFire();
}

bool UWeaponComponent::CanFire() const
{
	return CurrentWeapon && !bEquipAnimInProgress && !bReloadAnimInProgress;
}

void UWeaponComponent::StopFire()
{
	if (CurrentWeapon == nullptr)
	{
		return;
	}

	CurrentWeapon->StopFire();
}

void UWeaponComponent::SwitchWeapon()
{
	if (!CanEquip())
	{
		return;	
	}
	
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

bool UWeaponComponent::CanEquip() const
{
	return !bEquipAnimInProgress && !bReloadAnimInProgress;
}

void UWeaponComponent::Reload()
{
	ChangeClip();
}

bool UWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}

	return false;
}

bool UWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}

	return false;
}

ACharacter* UWeaponComponent::GetWeaponOwner() const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	return Character ? Character : nullptr;
}

bool UWeaponComponent::TryToAddAmmo(const TSubclassOf<ABaseWeapon> WeaponType, const int32 ClipsAmount)
{
	for (const auto Weapon: Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return Weapon->TryToAddAmmo(ClipsAmount);
		}
	}
	
	return false;
}

