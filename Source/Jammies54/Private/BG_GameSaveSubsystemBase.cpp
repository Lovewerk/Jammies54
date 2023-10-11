// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_GameSaveSubsystemBase.h"
#include "BG_SaveGameBase.h"
#include <Kismet/GameplayStatics.h>

void UBG_GameSaveSubsystemBase::Initialize(FSubsystemCollectionBase& Collection)
{
	PrepareSaveSlot();
}

void UBG_GameSaveSubsystemBase::SaveGame()
{
	if (!IsValid(myCurrentSave))
	{
		myCurrentSave = Cast<UBG_SaveGameBase>(UGameplayStatics::CreateSaveGameObject(UBG_SaveGameBase::StaticClass()));
	}

	if (IsValid(myCurrentSave))
	{
		// create a callback to handle completion of save
		FAsyncSaveGameToSlotDelegate OnSaveCompletedDelegate;
		OnSaveCompletedDelegate.BindUObject(this, &UBG_GameSaveSubsystemBase::HandleSaveComplete);

		// allow all listeners to set their data in the save file
		myOnSaveStartedDelegate.Broadcast(myCurrentSave);

		// save the game to disk
		UGameplayStatics::AsyncSaveGameToSlot(myCurrentSave, myDefaultSlot, myDefaultUserIndex, OnSaveCompletedDelegate);
	}
	else
	{
		checkNoEntry(); // somehow our save is not valid!
	}
}

void UBG_GameSaveSubsystemBase::LoadGame()
{
	// create a delegate to handle completion of load
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUObject(this, &UBG_GameSaveSubsystemBase::HandleLoadComplete);

	myOnLoadStartedDelegate.Broadcast();

	UGameplayStatics::AsyncLoadGameFromSlot(myDefaultSlot, myDefaultUserIndex, LoadedDelegate);
}

void UBG_GameSaveSubsystemBase::ClearGameData()
{

}

void UBG_GameSaveSubsystemBase::HandleSaveComplete(const FString& aSlotName, const int32 aUserIndex, bool bSuccess)
{
	if (bSuccess)
	{
		//UE_LOG(LogTemp, Warning, TEXT("mapSize After Load: %d"), myCurrentSave->myActorMap.Num());
		myOnSaveCompletedDelegate.Broadcast(); // saving is finished!
	}
	else
	{
		checkNoEntry(); // the save failed! #CLOVE_TODO: how will we handle this and what circumstances will cause it?
	}
}

void UBG_GameSaveSubsystemBase::HandleLoadComplete(const FString& aSlotName, const int32 aUserIndex, USaveGame* aLoadedGameData)
{
	if (IsValid(aLoadedGameData))
	{
		myCurrentSave = Cast<UBG_SaveGameBase>(aLoadedGameData);

		myOnLoadCompletedDelegate.Broadcast(myCurrentSave);
	}
	else
	{
		//checkNoEntry(); // #CLOVE_TODO: loading failed, how should we handle this?
	}
}

void UBG_GameSaveSubsystemBase::PrepareSaveSlot()
{
	if (!IsValid(myCurrentSave))
	{
		myCurrentSave = Cast<UBG_SaveGameBase>(UGameplayStatics::CreateSaveGameObject(UBG_SaveGameBase::StaticClass()));
	}
	else
	{
		LoadGame();
	}
}
