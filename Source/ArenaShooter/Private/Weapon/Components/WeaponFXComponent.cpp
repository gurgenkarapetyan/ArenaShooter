// Arena Shooter


#include "Components/WeaponFXComponent.h"
#include "Weapon/Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

UWeaponFXComponent::UWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult) const
{
	FImpactData ImpactData = DefaultImpactData;

	if (HitResult.PhysMaterial.IsValid())
	{
		const UPhysicalMaterial* PhysicalMaterial = HitResult.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysicalMaterial))
		{
			ImpactData = ImpactDataMap[PhysicalMaterial];
		}
	}
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

	UDecalComponent* const DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(),
		ImpactData.DecalData.Material,
		ImpactData.DecalData.Size,
		HitResult.ImpactPoint,
		HitResult.ImpactNormal.Rotation()
	);

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}
}

