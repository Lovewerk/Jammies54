// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "BG_AudioSubsystem.generated.h"


namespace FMOD::Studio
{
	class System;
}

UCLASS()
class JAMMIES54_API UBG_AudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	class FMOD::Studio::System* myStudioSystem;
	

public:
	float dBToLinear(float dB);
	void SetVCAVolume(const FString& aVCAName, const float& aLinearVolume);


	// Constants
	const FString myMusicVCAName{ "Music" };
	const FString mySFXVCAName{ "SFX" };

	UFUNCTION(BlueprintCallable)
	FString GetMusicVCAName() const { return myMusicVCAName; };
	UFUNCTION(BlueprintCallable)
	FString GetSFXVCAName() const { return myMusicVCAName; };
	
};
