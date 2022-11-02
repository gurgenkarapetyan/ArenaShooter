// Arena Shooter


#include "AI/Services/ChangeWeaponService.h"

#include "AIController.h"
#include "WeaponComponent.h"
#include "Utils/Utils.h"

UChangeWeaponService::UChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void UChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController* const AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		UWeaponComponent* const WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(AIController->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->SwitchWeapon();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
