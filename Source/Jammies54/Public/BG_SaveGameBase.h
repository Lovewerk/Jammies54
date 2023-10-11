// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include <Core/BG_GameData.h>
#include "BG_SaveGameBase.generated.h"

/**
 * 
 */
UCLASS()
class JAMMIES54_API UBG_SaveGameBase : public USaveGame
{
	GENERATED_BODY()

	UBG_SaveGameBase();

private:
	const int32 mySaveVersion = 0; // theoretically allow us to handle outdated save files
	UPROPERTY()
	FString mySaveSlotName;
	UPROPERTY()
	int32 mySaveUserIndex;

	UPROPERTY()
	UBG_GameData* myGameData;

public:

	UFUNCTION(BlueprintCallable)
	int32 GetSaveVersion() const;

	UFUNCTION(BlueprintCallable)
	void SetNameAndUserIndex(const FString& aSlotName, const int32 aUserIndex);

	UFUNCTION(BlueprintCallable)
	FString GetSaveSlotName();
	UFUNCTION(BlueprintCallable)
	int32 GetSaveUserIndex();

	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	//Pass back by reference
	UBG_GameData* GetGameData();

	//Get a reference to the level data contained in the SaveGame's GameData
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UBG_LevelData* GetLevelData();

	//Get a reference to player data contained in the SaveGame's GameData
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UBG_PlayerData* GetPlayerData();
};
