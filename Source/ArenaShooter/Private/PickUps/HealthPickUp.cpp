// Arena Shooter


#include "PickUps/HealthPickUp.h"

#include "HealthComponent.h"
#include "Utils/Utils.h"

bool AHealthPickUp::GivePickUpTo(APawn* PlayerPawn)
{
	UHealthComponent* HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(PlayerPawn);
	if (HealthComponent == nullptr)
	{
		return false;
	}
	
	return HealthComponent->TryToAddHealth(HealthAmount);
}
