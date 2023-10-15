// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_SaveableComponent.h"
#include <Kismet/GameplayStatics.h>
#include "BG_GameSaveSubsystemBase.h"

#include "Misc/Guid.h"
#include "BG_SaveGameBase.h"
#include <Serialization/ObjectAndNameAsStringProxyArchive.h>


// Sets default values for this component's properties
UBG_SaveableComponent::UBG_SaveableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UBG_SaveableComponent::InitializeComponent()
{
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
			/*saveSystem->myOnSaveCompletedDelegate.AddUObject(this, &UBG_SaveableComponent::HandleSaveCompleted); // Do we care about these?
			saveSystem->myOnLoadStartedDelegate.AddUObject(this, &UBG_SaveableComponent::HandleLoadStarted);*/
			saveSystem->myOnLoadCompletedDelegate.AddUObject(this, &UBG_SaveableComponent::HandleLoadCompleted);
		}
	}
}


// Called when the game starts
void UBG_SaveableComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UBG_SaveableComponent::HandleSaveStarted(UBG_SaveGameBase* aSaveGame)
{
	if (IsValid(aSaveGame))
	{
		if (myOnBeforeSerializeDelegate.IsBound())
		{
			myOnBeforeSerializeDelegate.Broadcast(this); // allow our owner to copy over save data before we serialize it
		}


		//pass in the array that we should fill with our actor's "SaveGame" variables once they are serialized to byte array
		FMemoryWriter memoryWriter(myCurrentData.myByteData);

		//make an Archive which uses the memory writer. The Archive actually handles the conversion to byte array
		FObjectAndNameAsStringProxyArchive archive(memoryWriter, true);

		archive.ArIsSaveGame = true; // only include variables marked as "SaveGame"

		if (AActor* owner = GetOwner())
		{
			owner->Serialize(archive); // owner's "SaveGame" variables are placed in the binary array that was given to the MemoryWriter
			

			// Figuring out how to save components programmatically will take an unknown amount of time. Going to just do it manually by copying data into the blueprint where needed. Can try to fix later.
			//TSet<UActorComponent*> components = owner->GetComponents();
			/*for (UActorComponent* component : components)
			{

			}*/

			// store additional data
			myCurrentData.myTransform = owner->GetTransform();
		}

		// store the byte array with this Saveable's GUID in the SaveGame's Map.
		aSaveGame->GetGameData().myData.Add(myGuid, myCurrentData);
	}
}

//void UBG_SaveableComponent::HandleSaveCompleted() const
//{
//	if (mySaveCompletedDelegate.IsBound())
//	{
//		mySaveCompletedDelegate.Broadcast();
//	}
//}
//void UBG_SaveableComponent::HandleLoadStarted() const
//{
//	if (myLoadStartedDelegate.IsBound())
//	{
//		myLoadStartedDelegate.Broadcast();
//	}
//}

void UBG_SaveableComponent::HandleLoadCompleted(const UBG_SaveGameBase* aSaveGame)
{
	// Handle converting our save data from byte array to its correct form. How will we cast to the correct class?
	// Maybe just keep it as the base? But how would we assign the values back...
	if (IsValid(aSaveGame))
	{
		if (aSaveGame->myGameData.myData.Contains(myGuid))
		{
			myCurrentData = aSaveGame->myGameData.myData[myGuid]; // get the byte array associated with this Saveable's GUID in the SaveGame's Map.
			FMemoryReader MemoryReader(myCurrentData.myByteData);

			FObjectAndNameAsStringProxyArchive Archive(MemoryReader, true);
			Archive.ArIsSaveGame = true;
			// Convert binary array back into actor's variables
			if (AActor* owner = GetOwner())
			{
				owner->Serialize(Archive);
			
				// Load additional actor data (that would not be stored on the derived instance)
				owner->SetActorTransform(myCurrentData.myTransform);
			}

			if (myOnAfterDeserializeDelegate.IsBound())
			{
				myOnAfterDeserializeDelegate.Broadcast(this);
			}
		}
	}
}

FGuid UBG_SaveableComponent::GetGuid_Implementation()
{
	return myGuid;
}

void UBG_SaveableComponent::SetGuid_Implementation(const FGuid& aGuid)
{
	myGuid = aGuid;
}