// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BG_GameData.generated.h"

// A base struct for data which should be saved, which will differ between different objects
USTRUCT(BlueprintType)
struct FBG_SaveableDataBase
{
	GENERATED_BODY()
};



USTRUCT(BlueprintType)
struct FBG_ButtonData : public FBG_SaveableDataBase
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		bool bMyIsPressed;


};

USTRUCT(BlueprintType)
struct FBG_LevelData
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		TMap<FString, FBG_SaveableDataBase> myData;

		
};

USTRUCT(BlueprintType)
struct FBG_PlayerData
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		int32 myData;

		// map of {inventory class, int quantity}
			// could be money, consumables, etc.
};

USTRUCT(BlueprintType)
struct FBG_GameData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FBG_PlayerData myPlayerData;

	UPROPERTY(BlueprintReadWrite)
	FBG_LevelData myLevelData;
};
