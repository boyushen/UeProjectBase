// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameUIPolicy.generated.h"
class UOverAllUILayout;
class UCommonLocalPlayer;

USTRUCT()
struct FRootViewportLayoutInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(Transient)
		ULocalPlayer* LocalPlayer = nullptr;

	UPROPERTY(Transient)
		UOverAllUILayout* RootLayout = nullptr;

	UPROPERTY(Transient)
		bool bAddedToViewport = false;

	FRootViewportLayoutInfo() {}
	FRootViewportLayoutInfo(ULocalPlayer* InLocalPlayer, UOverAllUILayout* InRootLayout, bool bIsInViewport)
		: LocalPlayer(InLocalPlayer)
		, RootLayout(InRootLayout)
		, bAddedToViewport(bIsInViewport)
	{}

	bool operator==(const ULocalPlayer* OtherLocalPlayer) const { return LocalPlayer == OtherLocalPlayer; }
};
/**
 * 
 */
UCLASS(Abstract, Blueprintable, Within = GameUIManagerSubsystem)
class RAPROJECT_API UGameUIPolicy : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
		TSoftClassPtr<UOverAllUILayout> layoutClassBase;

public:
	void NotifyPlayerAdded(UCommonLocalPlayer* LocalPlayer);
	void NotifyPlayerDestory(UCommonLocalPlayer* LocalPlayer);
	void CreateLayoutWidget(UCommonLocalPlayer* LocalPlayer);
	void AddLayoutToViewport(UCommonLocalPlayer* LocalPlayer, UOverAllUILayout* Layout);
	void RemoveLayoutToViewport(UCommonLocalPlayer* LocalPlayer, UOverAllUILayout* Layout);
	UOverAllUILayout* GetRootLayout(UCommonLocalPlayer* LocalPlayer);
private:
	UPROPERTY()
	//TMap<UCommonLocalPlayer*, UOverAllUILayout*> playerUILayoutMap;
	TArray<FRootViewportLayoutInfo> playerUILayouts;
};
