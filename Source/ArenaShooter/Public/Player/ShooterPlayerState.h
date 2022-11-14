// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShooterPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API AShooterPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetTeamID(const int32 ID) { TeamID = ID; }
	FORCEINLINE int32 GetTeamID() const { return TeamID; }

	FORCEINLINE void SetTeamColor(const FLinearColor Color) { TeamColor = Color; }
	FORCEINLINE FLinearColor GetTeamColor() const { return TeamColor; }

private:
	int32 TeamID;

	FLinearColor TeamColor;
};
