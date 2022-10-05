// Arena Shooter


#include "Components/ShooterMovementComponent.h"
#include "Player/ShooterBaseCharacter.h"

float UShooterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();

	const AShooterBaseCharacter* const Player = Cast<AShooterBaseCharacter>(GetPawnOwner());
	
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
