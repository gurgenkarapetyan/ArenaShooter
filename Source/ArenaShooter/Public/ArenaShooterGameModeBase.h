// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "ArenaShooterGameModeBase.generated.h"

class AAIController;

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API AArenaShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AArenaShooterGameModeBase();

	virtual void StartPlay() override;

	/** Returns default pawn class for given controller */
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

private:
	/** Spawn bots when game starts. */
	void SpawnBots();

	/** Handle start round functionality. */
	void StartRound();

	/** Update game timer and set game round. */
	void GameTimerUpdate();

	/** Iterate through all Players in the world and reset them. */
	void ResetPlayers();

	/** Reset Player with found controller.
	 * @param Controller - player controller to reset.
	 */
	void ResetOnePlayer(AController* Controller);

	/** Allocate players to teams. */
	void CreateTeamsInfo() const;
	
	FLinearColor DetermineColorByTeamID(int32 TeamID) const;
	
	void SetPlayerColor(const AController* Controller) const;
	
protected:
	/** class of controller to be spawned on game start. */
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	/** class of pawn to be spawned on game start. */
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	/** Information of game data when game starts. */
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

private:
	/** Store information about current round. */
	int32 CurrentRound = 1;

	/** Store current round time information. */
	int32 RoundCountDown = 0;

	/** Timer handler for each round. */
	FTimerHandle GameRoundTimerHandle;
};
