// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "RAWorldSettings.generated.h"
class UExperienceDefinition;
/**
 * 
 */
UCLASS()
class RAPROJECT_API ARAWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
public:
	// Returns the default experience to use when a server opens this map if it is not overridden by the user-facing experience
	FPrimaryAssetId GetDefaultGameplayExperience() const;

protected:
	// The default experience to use when a server opens this map if it is not overridden by the user-facing experience
	UPROPERTY(EditDefaultsOnly, Category = GameMode)
		TSoftClassPtr<UExperienceDefinition> DefaultGameplayExperience;
};
