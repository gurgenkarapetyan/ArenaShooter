// Arena Shooter


#include "Components/WeaponComponent.h"

#include "BaseWeapon.h"
#include "EquipFinishedAnimNotify.h"
#include "GameFramework/Character.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

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
	
	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
		if (Weapon == nullptr)
		{
			continue;
		}

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
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
	const ACharacter* const Character = GetWeaponOwner();

	if (CurrentWeapon)
	{
		StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}
	
	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	PlayAnimMontage(EquipAnimMontage);
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) const
{
	ACharacter* const Character = GetWeaponOwner();

	Character->PlayAnimMontage(Animation);
}

void UWeaponComponent::InitAnimations()
{
	if (EquipAnimMontage == nullptr)
	{
		return;
	}
	
	const TArray<FAnimNotifyEvent> NotifyEvents = EquipAnimMontage->Notifies;
	for (const FAnimNotifyEvent NotifyEvent : NotifyEvents)
	{
		UEquipFinishedAnimNotify* const EquipFinishNotify = Cast<UEquipFinishedAnimNotify>(NotifyEvent.Notify);
		if (EquipFinishNotify)
		{
			EquipFinishNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipFinished);
			break;
		}
	}
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	const ACharacter* const Character = GetWeaponOwner();
	
	if (Character->GetMesh() != MeshComponent)
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("ONEQUIPFINISHED"));
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
	if (CurrentWeapon == nullptr)
	{
		return;
	}

	CurrentWeapon->StartFire();
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
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

ACharacter* UWeaponComponent::GetWeaponOwner() const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	return Character ? Character : nullptr;
}