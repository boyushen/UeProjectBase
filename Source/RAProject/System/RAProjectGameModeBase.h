// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RAProjectGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class RAPROJECT_API ARAProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ARAProjectGameModeBase(const FObjectInitializer& ObjectInitializer);
	//~AGameModeBase interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	//virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	//virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	//virtual bool ShouldSpawnAtStartSpot(AController* Player) override;
	//virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	//virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	//virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;
	//virtual bool PlayerCanRestart_Implementation(APlayerController* Player) override;
	//virtual void InitGameState() override;
	//~End of AGameModeBase interface

	void HandleMatchAssignmentIfNotExpectingOne();
	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId);
};
