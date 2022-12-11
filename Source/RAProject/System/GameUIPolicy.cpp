// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUIPolicy.h"
#include "Engine/LocalPlayer.h"
#include "CommonLocalPlayer.h"
#include "../UI/OverAllUILayout.h"
#include "Engine/Engine.h"
void UGameUIPolicy::NotifyPlayerAdded(UCommonLocalPlayer* LocalPlayer)
{
	ensure(LocalPlayer);
	UE_LOG(LogTemp, Error, TEXT("AddUser"));
	if (auto ass = playerUILayouts.FindByKey(LocalPlayer)) {
		AddLayoutToViewport(LocalPlayer, ass->RootLayout);
		ass->bAddedToViewport = true;
	}
	else
	{
		LocalPlayer->OnPlayerControllerSet.AddWeakLambda(this, [this](UCommonLocalPlayer* LocalPlayer, APlayerController* PlayerController)
		{
		UE_LOG(LogTemp, Error, TEXT("AddUser"));
		CreateLayoutWidget(LocalPlayer);
		});

	}

}
void UGameUIPolicy::NotifyPlayerDestory(UCommonLocalPlayer* LocalPlayer)
{
	LocalPlayer->OnPlayerControllerSet.RemoveAll(this);
	if (auto ass = playerUILayouts.FindByKey(LocalPlayer)) {
		RemoveLayoutToViewport(LocalPlayer, ass->RootLayout);

	}
}
void UGameUIPolicy::CreateLayoutWidget(UCommonLocalPlayer* LocalPlayer)
{
	UE_LOG(LogTemp, Error, TEXT("SET OVERALL LAYOUT"));
	
	if (layoutClassBase.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("ISNULL"));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("ADD VIEWPORT"));
	TSubclassOf<UOverAllUILayout> LayoutWidgetClass = layoutClassBase.LoadSynchronous();
	if (ensure(LayoutWidgetClass) && !LayoutWidgetClass->HasAnyClassFlags(CLASS_Abstract)) {
		UOverAllUILayout* layoutObject = CreateWidget<UOverAllUILayout>(LocalPlayer->GetPlayerController(GetWorld()), LayoutWidgetClass);
		AddLayoutToViewport(LocalPlayer, layoutObject);
	}
}
void UGameUIPolicy::AddLayoutToViewport(UCommonLocalPlayer* LocalPlayer, UOverAllUILayout* Layout)
{
	//UE_LOG(LogTemp, Log, TEXT("DefaultUIPolicyClass Is not Null"));
	UE_LOG(LogTemp, Log, TEXT("[%s] is adding player [%s]'s root layout [%s] to the viewport"),
		*GetName(),
		*GetNameSafe(LocalPlayer), *GetNameSafe(Layout));

	Layout->SetPlayerContext(FLocalPlayerContext(LocalPlayer));
	Layout->AddToPlayerScreen(1000);

}
void UGameUIPolicy::RemoveLayoutToViewport(UCommonLocalPlayer* LocalPlayer, UOverAllUILayout* Layout)
{
	Layout->RemoveFromViewport();
	Layout->RemoveFromParent();
}
UOverAllUILayout* UGameUIPolicy::GetRootLayout(UCommonLocalPlayer* LocalPlayer)
{
	const FRootViewportLayoutInfo* LayoutInfo = playerUILayouts.FindByKey(LocalPlayer);
	check(LayoutInfo);
	return LayoutInfo->RootLayout;
}