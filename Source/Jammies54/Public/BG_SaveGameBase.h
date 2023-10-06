// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BG_SaveGameBase.generated.h"

/**
 * 
 */
UCLASS()
class JAMMIES54_API UBG_SaveGameBase : public USaveGame
{
	GENERATED_BODY()

public:
		UPROPERTY(BlueprintReadWrite)
		int myTestValue;
	
};
