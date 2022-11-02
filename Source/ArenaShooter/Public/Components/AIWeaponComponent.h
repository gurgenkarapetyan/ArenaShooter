// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "Components/WeaponComponent.h"
#include "AIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API UAIWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void SwitchWeapon() override;
	
};
