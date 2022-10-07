// Arena Shooter


#include "ArenaShooterGameModeBase.h"

#include "GameHUD.h"
#include "Player/ShooterBaseCharacter.h"
#include "Player/ShooterPlayerController.h"

AArenaShooterGameModeBase::AArenaShooterGameModeBase()
{
	DefaultPawnClass = AShooterBaseCharacter::StaticClass();
	PlayerControllerClass = AShooterPlayerController::StaticClass();
	HUDClass = AGameHUD::StaticClass();
}
