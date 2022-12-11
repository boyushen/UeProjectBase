// Fill out your copyright notice in the Description page of Project Settings.


#include "RAProjectGameModeBase.h"
#include "TimerManager.h"
#include "RAWorldSettings.h"
#include "GameFeatureAction.h"
#include "GameFeaturesSubsystem.h"
#include "GameFeaturesSubsystemSettings.h"
#include "ExperienceDefinition.h"
#include "Engine/AssetManager.h"
#include "CommonPlayerController.h"
ARAProjectGameModeBase::ARAProjectGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = ACommonPlayerController::StaticClass();
}
void ARAProjectGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void ARAProjectGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{
	FPrimaryAssetId ExperienceId;
	auto world = GetWorld();
	if (!ExperienceId.IsValid()) {
		if (auto worldSetting = Cast<ARAWorldSettings>(GetWorldSettings()))
		{
			ExperienceId = worldSetting->GetDefaultGameplayExperience();
		}
	}
	OnMatchAssignmentGiven(ExperienceId);
}

void ARAProjectGameModeBase::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId)
{
	if (!ExperienceId.IsValid()) { return; }

	UAssetManager& AssetManager = UAssetManager::Get();
	FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(ExperienceId);
	TSubclassOf<UExperienceDefinition> AssetClass = Cast<UClass>(AssetPath.TryLoad());
	check(AssetClass);
	const UExperienceDefinition* Experience = GetDefault<UExperienceDefinition>(AssetClass);

	// Execute the actions
	FGameFeatureActivatingContext Context;
	// Only apply to our specific world context if set
	const FWorldContext* ExistingWorldContext = GEngine->GetWorldContextFromWorld(GetWorld());
	if (ExistingWorldContext)
	{
		Context.SetRequiredWorldContextHandle(ExistingWorldContext->ContextHandle);
	}

	auto ActivateListOfActions = [&Context](const TArray<UGameFeatureAction*>& ActionList)
	{
		for (UGameFeatureAction* Action : ActionList)
		{
			if (Action != nullptr)
			{
				//@TODO: The fact that these don't take a world are potentially problematic in client-server PIE
				// The current behavior matches systems like gameplay tags where loading and registering apply to the entire process,
				// but actually applying the results to actors is restricted to a specific world
				Action->OnGameFeatureRegistering();
				Action->OnGameFeatureLoading();
				Action->OnGameFeatureActivating(Context);
			}
		}
	};
	ActivateListOfActions(Experience->Actions);
}

