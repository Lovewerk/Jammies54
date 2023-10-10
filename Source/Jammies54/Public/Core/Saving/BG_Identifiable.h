// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BG_Identifiable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBG_Identifiable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JAMMIES54_API IBG_Identifiable
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveSystem|Identifiable")
	FGuid GetGuid();

	// Pick a GUID
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveSystem|Identifiable")
	void SetGuid(const FGuid& aGuid);
};
