// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExperienceDefinition.generated.h"
class UGameFeatureAction;
/**
 * 
 */
UCLASS(BlueprintType, Const)
class RAPROJECT_API UExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UExperienceDefinition();
	//~UObject interface
#if WITH_EDITOR
	//virtual EDataValidationResult IsDataValid(TArray<FText>& ValidationErrors) override;
#endif
	//~End of UObject interface

	//~UPrimaryDataAsset interface
#if WITH_EDITORONLY_DATA
	//virtual void UpdateAssetBundleData() override;
#endif
public:
	// List of actions to perform as this experience is loaded/activated/deactivated/unloaded
	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Actions")
		TArray<UGameFeatureAction*> Actions;
};
