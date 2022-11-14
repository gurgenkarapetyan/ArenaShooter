// Arena Shooter


#include "ArenaShooterGameModeBase.h"

#include "AIController.h"
#include "GameHUD.h"
#include "ShooterPlayerState.h"
#include "Player/ShooterBaseCharacter.h"
#include "Player/ShooterPlayerController.h"

AArenaShooterGameModeBase::AArenaShooterGameModeBase()
{
	DefaultPawnClass = AShooterBaseCharacter::StaticClass();
	PlayerControllerClass = AShooterPlayerController::StaticClass();
	HUDClass = AGameHUD::StaticClass();
	PlayerStateClass = AShooterPlayerState::StaticClass();
}

void AArenaShooterGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();
	
	CurrentRound = 1;
	StartRound();
}

void AArenaShooterGameModeBase::SpawnBots()
{
	if (GetWorld() == nullptr)
	{
		return;
	}

	for (int32 i = 0; i < GameData.PlayersNum - 1; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AController* const AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(AIController);
	}
}

void AArenaShooterGameModeBase::CreateTeamsInfo() const
{
	 if (GetWorld() == nullptr)
	 {
	 	return;
	 }
	
	 int32 TeamID = 1;
	 for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
	 {
	 	const AController* const Controller = It->Get();
	 	if (Controller == nullptr)
	 	{
	 		continue;
	 	}
	
	 	AShooterPlayerState* const PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
	 	if (PlayerState  == nullptr)
	 	{
	 		continue;
	 	}
	
	 	PlayerState->SetTeamID(TeamID);
	 	PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
	 	SetPlayerColor(Controller);
	 	
	 	TeamID = TeamID == 1 ? 2 : 1;
	 }
}

 FLinearColor AArenaShooterGameModeBase::DetermineColorByTeamID(const int32 TeamID) const
 {
 	if (TeamID - 1 < GameData.TeamColors.Num())
 	{
 		return GameData.TeamColors[TeamID - 1];
 	}

 	UE_LOG(LogTemp, Warning, TEXT("No color for team id: %i, set to default: %s"), TeamID, *GameData.DefaultTeamColor.ToString());
 	return GameData.DefaultTeamColor;
 }

 void AArenaShooterGameModeBase::SetPlayerColor(const AController* Controller) const
 {
 	if (Controller == nullptr)
 	{
 		return;
 	}

 	const AShooterBaseCharacter* const Character = Cast<AShooterBaseCharacter>(Controller->GetPawn());
 	if (Character == nullptr)
 	{
 		return;
 	}

 	const AShooterPlayerState* const PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
 	if (PlayerState == nullptr)
 	{
 		return;
 	}

 	Character->SetPlayerColor(PlayerState->GetTeamColor());
 }

void AArenaShooterGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AArenaShooterGameModeBase::GameTimerUpdate, 1.f, true);
}

void AArenaShooterGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogTemp, Warning, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);
	
	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("----- GAME OVER ------"));
		}
	}
}

void AArenaShooterGameModeBase::ResetPlayers()
{
	if (GetWorld() == nullptr)
	{
		return;
	}

	for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void AArenaShooterGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

UClass* AArenaShooterGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}
