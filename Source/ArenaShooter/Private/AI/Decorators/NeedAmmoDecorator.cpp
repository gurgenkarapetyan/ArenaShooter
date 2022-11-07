// Arena Shooter


#include "AI/Decorators/NeedAmmoDecorator.h"

#include "AIController.h"
#include "BaseWeapon.h"
#include "WeaponComponent.h"
#include "Utils/Utils.h"

UNeedAmmoDecorator::UNeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool UNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	const AAIController* const AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr || WeaponType == nullptr)
	{
		return false;
	}

	UWeaponComponent* const WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(AIController->GetPawn());
	if (WeaponComponent == nullptr)
	{
		return false;
	}
	
	return WeaponComponent->NeedAmmo(WeaponType);
}
