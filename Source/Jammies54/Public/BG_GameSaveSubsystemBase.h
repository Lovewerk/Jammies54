// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BG_GameSaveSubsystemBase.generated.h"

class USaveGame;
class UBG_SaveGameBase;

DECLARE_MULTICAST_DELEGATE(FOnPrepareSaveSlotCompletedDelegate);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSaveStartedSignature, UBG_SaveGameBase* /*, aSaveGame*/);
DECLARE_MULTICAST_DELEGATE(FOnSaveCompletedSignature);
DECLARE_MULTICAST_DELEGATE(FOnLoadStartedSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoadCompletedSignature, const UBG_SaveGameBase* /*, aSaveGame*/);


UCLASS()
class JAMMIES54_API UBG_GameSaveSubsystemBase : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBG_SaveGameBase* myCurrentSave;

	UPROPERTY()
	FString myDefaultSlot = "SaveSlot01";
	UPROPERTY()
	int32 myDefaultUserIndex = 0;

	FDelegateHandle myResumeSaveAfterPrepareSaveSlotHandle;
	FDelegateHandle myOnLoadCompletedWhenPrepareExistingSaveHandle;

	void HandlePrepareSaveSlotComplete(const FString& aSlotName, const int32 aUserIndex, USaveGame* aLoadedSaveGame);
	void HandleSaveComplete(const FString& aSlotName, const int32 aUserIndex, bool bSuccess);
	void HandleLoadComplete(const FString& aSlotName, const int32 aUserIndex, USaveGame* aLoadedGameData);

public:

	FOnPrepareSaveSlotCompletedDelegate myOnPrepareSaveSlotCompletedDelegate;

	FOnSaveStartedSignature myOnSaveStartedDelegate;
	FOnSaveCompletedSignature myOnSaveCompletedDelegate;
	FOnLoadStartedSignature myOnLoadStartedDelegate;
	FOnLoadCompletedSignature myOnLoadCompletedDelegate;


public:
	//Create a save game, or load if one already exists
	UFUNCTION(BLueprintCallable)
		void PrepareSaveSlot();

	//Save to the given slotName and userIndex
	UFUNCTION(BlueprintCallable)
		void SaveGame();

	UFUNCTION(BlueprintCallable)
		void LoadGame();

	UFUNCTION(BlueprintCallable)
		void ClearGameData();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
