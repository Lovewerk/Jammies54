// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BG_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JAMMIES54_API UBG_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	bool bMyReloadSaveOnNewWorldInit; //used for ensuring when we restart our current level, that we start from the last save.
	
};
