// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_GameSaveSubsystemBase.h"
#include "BG_SaveGameBase.h"
#include <Kismet/GameplayStatics.h>
#include "Core/BG_GameInstance.h"

#include "../Jammies54.h" // for debug categories

void UBG_GameSaveSubsystemBase::Initialize(FSubsystemCollectionBase& Collection)
{
	//#CLOVE_CRASH: inside the lambda on the if statement
	/*FWorldDelegates::OnWorldInitializedActors.AddLambda([this](const FActorsInitializedParams& actorParams)
	{
		if(UBG_GameInstance* gameInstance = Cast<UBG_GameInstance>(GetGameInstance()))
		{
			if (gameInstance->bMyReloadSaveOnNewWorldInit)
			{
				gameInstance->bMyReloadSaveOnNewWorldInit = false;
				LoadGame();
			}
		}
	}
	);*/
	PrepareSaveSlot();
}

void UBG_GameSaveSubsystemBase::SaveGame()
{
	if (!IsValid(myCurrentSave) && !UGameplayStatics::DoesSaveGameExist(myDefaultSlot, myDefaultUserIndex))
	{
		UE_LOG(BG_SAVE_SYSTEM, Warning, TEXT("Attempted Save with no current save and no save exists on disk for current slot. Will attempt to prepare a new save slot."));
		myResumeSaveAfterPrepareSaveSlotHandle = myOnPrepareSaveSlotCompletedDelegate.AddUObject(this, &UBG_GameSaveSubsystemBase::SaveGame);
		PrepareSaveSlot();
		return;
	}

	if (IsValid(myCurrentSave))
	{
		// unsubscribe from handling completion of prepare save slot (may have subscribed above, needed for the possible async load in prepareSaveSlot
		myOnPrepareSaveSlotCompletedDelegate.Remove(myResumeSaveAfterPrepareSaveSlotHandle);

		// create a callback to handle completion of save
		FAsyncSaveGameToSlotDelegate OnSaveCompletedDelegate;
		OnSaveCompletedDelegate.BindUObject(this, &UBG_GameSaveSubsystemBase::HandleSaveComplete);

		// allow all listeners to set their data in the save file
		if (myOnSaveStartedDelegate.IsBound())
		{
			myOnSaveStartedDelegate.Broadcast(myCurrentSave);
		}

		myCurrentSave->isPressed = true;

		// save the game to disk
		UE_LOG(BG_SAVE_SYSTEM, Log, TEXT("Begin async save"));
		UGameplayStatics::AsyncSaveGameToSlot(myCurrentSave, myDefaultSlot, myDefaultUserIndex, OnSaveCompletedDelegate);
	}
	else
	{
		UE_LOG(BG_SAVE_SYSTEM, Error, TEXT("Attempted to save and slot exists, but current save in the SaveGame is invalid."));
	}
}

void UBG_GameSaveSubsystemBase::LoadGame()
{
	// create a delegate to handle completion of load
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUObject(this, &UBG_GameSaveSubsystemBase::HandleLoadComplete);

	UE_LOG(BG_SAVE_SYSTEM, Log, TEXT("Begin loading save data!"));
	if (myOnLoadStartedDelegate.IsBound())
	{
		myOnLoadStartedDelegate.Broadcast();
	}

	UGameplayStatics::AsyncLoadGameFromSlot(myDefaultSlot, myDefaultUserIndex, LoadedDelegate);
}

void UBG_GameSaveSubsystemBase::ClearGameData()
{
	if (UGameplayStatics::DeleteGameInSlot(myDefaultSlot, myDefaultUserIndex))
	{
		UE_LOG(BG_SAVE_SYSTEM, Warning, TEXT("Deleted save in slot %s!"), *myDefaultSlot);
	}
}

void UBG_GameSaveSubsystemBase::HandleSaveComplete(const FString& aSlotName, const int32 aUserIndex, bool bSuccess)
{
	if (bSuccess)
	{
		if (myOnSaveCompletedDelegate.IsBound())
		{
			myOnSaveCompletedDelegate.Broadcast();
		} // saving is finished!
		UE_LOG(BG_SAVE_SYSTEM, Log, TEXT("Saving game completed successfully!"));
	}
	else
	{
		UE_LOG(BG_SAVE_SYSTEM, Error, TEXT("Saving game failed!"));
		checkNoEntry(); // the save failed! #CLOVE_TODO: how will we handle this and what circumstances will cause it?
	}
}

void UBG_GameSaveSubsystemBase::HandleLoadComplete(const FString& aSlotName, const int32 aUserIndex, USaveGame* aLoadedSaveGame)
{
	if (IsValid(aLoadedSaveGame))
	{
		myCurrentSave = Cast<UBG_SaveGameBase>(aLoadedSaveGame);

		if (IsValid(myCurrentSave))
		{
			UE_LOG(BG_SAVE_SYSTEM, Log, TEXT("Load completed successfully!"));
			if (myOnLoadCompletedDelegate.IsBound())
			{
				myOnLoadCompletedDelegate.Broadcast(myCurrentSave);
			}
		}
		else
		{
			UE_LOG(BG_SAVE_SYSTEM, Error, TEXT("Loading save game But casting to desired subclass failed."));
		}
	}
	else
	{
		//checkNoEntry(); // #CLOVE_TODO: loading failed, how should we handle this?
		UE_LOG(BG_SAVE_SYSTEM, Error, TEXT("Loading save game failed! Did not receive a valid SaveGame on load completion."));
	}
}

void UBG_GameSaveSubsystemBase::PrepareSaveSlot()
{
	if (UGameplayStatics::DoesSaveGameExist(myDefaultSlot, myDefaultUserIndex))
	{
		myOnLoadCompletedWhenPrepareExistingSaveHandle = myOnLoadCompletedDelegate.AddLambda(
			[this](const USaveGame* aLoadedSaveGame)
			{
				// loading caches the SaveGame, so my can just notify of completion with that cached value
				if (myOnPrepareSaveSlotCompletedDelegate.IsBound()) 
				{
					myOnPrepareSaveSlotCompletedDelegate.Broadcast();
				}

				//ensure we don't accidentally call this lambda again if loading triggered from a different source
				myOnLoadCompletedDelegate.Remove(myOnLoadCompletedWhenPrepareExistingSaveHandle);
				UE_LOG(BG_SAVE_SYSTEM, Log, TEXT("Remove listener from prepareSaveSlotComplete event"));
			}
		);

		LoadGame(); // once existing save finishes loading, the save slot is prepared
	}
	else
	{
		myCurrentSave = Cast<UBG_SaveGameBase>(UGameplayStatics::CreateSaveGameObject(UBG_SaveGameBase::StaticClass()));
		if (myCurrentSave)
		{
			if(myOnPrepareSaveSlotCompletedDelegate.IsBound())
			{
				myOnPrepareSaveSlotCompletedDelegate.Broadcast();
			}
		}
		else
		{
			UE_LOG(BG_SAVE_SYSTEM, Error, TEXT("On Creating a new save game, it was null!"));
			checkNoEntry();
		}
	}
}
