// Arena Shooter


#include "ArenaShooterGameModeBase.h"

#include "Player/ShooterBaseCharacter.h"
#include "Player/ShooterPlayerController.h"

AArenaShooterGameModeBase::AArenaShooterGameModeBase()
{
	DefaultPawnClass = AShooterBaseCharacter::StaticClass();
	PlayerControllerClass = AShooterPlayerController::StaticClass();
}
