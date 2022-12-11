// Fill out your copyright notice in the Description page of Project Settings.


#include "RAGameInstance.h"
#include "GameUIManagerSubsystem.h"
#include "Engine/LocalPlayer.h"
void URAGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Log, TEXT("URAGameInstance Init"));
}
int32 URAGameInstance::AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId ControllerId)
{
	Super::AddLocalPlayer(NewPlayer, ControllerId);
	UE_LOG(LogTemp, Log, TEXT("URAGameInstance AddLocalPlayer"));
	int32 ReturnVal = Super::AddLocalPlayer(NewPlayer, ControllerId);
	if (ReturnVal != INDEX_NONE)
	{
		UE_LOG(LogTemp, Error, TEXT("321"));
		GetSubsystem<UGameUIManagerSubsystem>()->NotifyPlayerAdded(Cast<ULocalPlayer>(NewPlayer));
	}
	return ReturnVal;
}
bool URAGameInstance::RemoveLocalPlayer(ULocalPlayer* ExistingPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("URAGameInstance RemoveLocalPlayer"));
	return Super::RemoveLocalPlayer(ExistingPlayer);
}