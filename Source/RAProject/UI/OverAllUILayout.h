// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "OverAllUILayout.generated.h"
class UCommonActivatableWidgetStack;
/**
 * 
 */
UCLASS()
class RAPROJECT_API UOverAllUILayout : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UCommonActivatableWidgetStack* GameUI_Layout;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UCommonActivatableWidgetStack* GameMenu_Layout;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UCommonActivatableWidgetStack* Menu_Layout;
};
