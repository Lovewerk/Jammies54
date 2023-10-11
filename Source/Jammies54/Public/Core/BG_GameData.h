// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BG_GameData.generated.h"

// A base for data which should be saved. Would use structs, but need UObjects for polymorphism in blueprints
UCLASS(BlueprintType, Blueprintable, Abstract)
class UBG_SaveableDataBase : public UObject
{
	GENERATED_BODY()
};



UCLASS(BlueprintType)
class UBG_ButtonData : public UBG_SaveableDataBase
{
	GENERATED_BODY()
public:
		UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
		bool bMyIsPressed;
};

UCLASS(BlueprintType)
class UBG_LevelData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TMap<FGuid, UBG_SaveableDataBase*> myData;
};

// #CLOVE_NOTE: Choosing to make the following data UObjects rather than USTRUCTS. Returning them from C++ to Blueprints by reference was more difficult than anticipated.

UCLASS(BlueprintType)
class UBG_PlayerData : public UObject
{
	GENERATED_BODY()

public:
		UPROPERTY(BlueprintReadWrite)
		TMap<FGuid, UBG_SaveableDataBase*> myData;

		// map of {inventory class, int quantity}
			// could be money, consumables, etc.
};

UCLASS(BlueprintType)
class UBG_GameData : public UObject
{
	GENERATED_BODY()

		UBG_GameData();

public:
	UPROPERTY(BlueprintReadWrite)
	UBG_PlayerData* myPlayerData;

	UPROPERTY(BlueprintReadWrite)
	UBG_LevelData* myLevelData;
};
