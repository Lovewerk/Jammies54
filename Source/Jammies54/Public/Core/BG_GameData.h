// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BG_GameData.generated.h"

USTRUCT(BlueprintType)
struct FBG_SaveableData
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	FTransform myTransform;
	UPROPERTY(SaveGame)
	TArray<uint8> myByteData;
};

USTRUCT(BlueprintType)
struct FBG_GameData
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	TMap<FGuid, FBG_SaveableData> myData;

};