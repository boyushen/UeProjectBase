// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUIManagerSubsystem.h"
#include "Engine/LocalPlayer.h"
#include "GameUIPolicy.h"
#include "CommonLocalPlayer.h"
void UGameUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("UGameUIManagerSubsystem::Initialize()"));
	if (!DefaultUIPolicyClass.IsNull())
	{
		UE_LOG(LogTemp, Log, TEXT("DefaultUIPolicyClass Is not Null"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("DefaultUIPolicyClass Is Null"));
	}
	
	if (!CurrentPolicy && !DefaultUIPolicyClass.IsNull()) {
		TSubclassOf<UGameUIPolicy> PolicyClass = DefaultUIPolicyClass.LoadSynchronous();
		SwitchToPolicy(NewObject<UGameUIPolicy>(this, PolicyClass));
	}
}

void UGameUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Log, TEXT("UGameUIManagerSubsystem::Deinitialize()"));
}

void UGameUIManagerSubsystem::NotifyPlayerAdded(ULocalPlayer* LocalPlayer)
{
	if (!CurrentPolicy)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Policy"));
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("NotifyPlayerAdded"));
	CurrentPolicy->NotifyPlayerAdded(Cast<UCommonLocalPlayer>(LocalPlayer));
}
void UGameUIManagerSubsystem::NotifyPlayerRemoved(ULocalPlayer* LocalPlayer) {

}
void UGameUIManagerSubsystem::NotifyPlayerDestroyed(ULocalPlayer* LocalPlayer)
{

}
void UGameUIManagerSubsystem::SwitchToPolicy(UGameUIPolicy* InPolicy)
{
	UE_LOG(LogTemp, Log, TEXT("SwitchToPolicy"));
	if (CurrentPolicy != InPolicy)
	{
		CurrentPolicy = InPolicy;
	}
}