// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "BG_AudioSubsystem.generated.h"


namespace FMOD::Studio
{
	class System;
}

UENUM(BlueprintType)
enum class EVCAName : uint8
{
	Music,
	SFX,
	Dialogue
};

UCLASS()
class JAMMIES54_API UBG_AudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	class FMOD::Studio::System* myStudioSystem;
	

public:
	UFUNCTION(BlueprintCallable)
	float dBToLinear(float dB);

	UFUNCTION(BlueprintCallable)
	void SetVCAVolume(const EVCAName aVCAName, const float& aLinearVolume);


	// Constants
	const FString myMusicVCAName{ "Music" };
	const FString mySFXVCAName{ "SFX" };

	UFUNCTION(BlueprintCallable)
	FString GetVCAName(const EVCAName aVCA) const;
	
};
