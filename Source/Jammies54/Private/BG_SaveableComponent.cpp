// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_SaveableComponent.h"
#include <Kismet/GameplayStatics.h>
#include "BG_GameSaveSubsystemBase.h"

#include "Misc/Guid.h"
#include "BG_SaveGameBase.h"
#include "../Jammies54.h"


// Sets default values for this component's properties
UBG_SaveableComponent::UBG_SaveableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UBG_SaveableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!myGuid.IsValid())
	{
		myGuid = FGuid::NewGuid();
	}

	// listen to save subsystem events
	if (UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UBG_GameSaveSubsystemBase* saveSystem = gameInstance->GetSubsystem<UBG_GameSaveSubsystemBase>())
		{
			saveSystem->myOnSaveStartedDelegate.AddUObject(this, &UBG_SaveableComponent::HandleSaveStarted);
			saveSystem->myOnSaveCompletedDelegate.AddUObject(this, &UBG_SaveableComponent::HandleSaveCompleted);
			saveSystem->myOnLoadStartedDelegate.AddUObject(this, &UBG_SaveableComponent::HandleLoadStarted);
			saveSystem->myOnLoadCompletedDelegate.AddUObject(this, &UBG_SaveableComponent::HandleLoadCompleted);
		}
	}	
}

void UBG_SaveableComponent::HandleSaveStarted(UBG_SaveGameBase* aSaveData)
{
	mySaveStartedDelegate.Broadcast(aSaveData);
}
void UBG_SaveableComponent::HandleSaveCompleted() const
{
	mySaveCompletedDelegate.Broadcast();
}
void UBG_SaveableComponent::HandleLoadStarted() const
{
	myLoadStartedDelegate.Broadcast();
}
void UBG_SaveableComponent::HandleLoadCompleted(const UBG_SaveGameBase* aSaveData) const
{
	myLoadCompletedDelegate.Broadcast(aSaveData);
}

FGuid UBG_SaveableComponent::GetGuid_Implementation()
{
	return myGuid;
}

void UBG_SaveableComponent::SetGuid_Implementation(const FGuid& aGuid)
{
	myGuid = aGuid;
}