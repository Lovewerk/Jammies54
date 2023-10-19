#include "Core/BG_Util.h"
#include "Kismet/GameplayStatics.h"
#include "../Jammies54.h"

UBG_GameInstance* UBG_Util::GetGameInstance(const UObject* aWorldContextObject, EConditionalOutput& someOutputs)
{
	UBG_GameInstance* gameInstance = Cast<UBG_GameInstance>(UGameplayStatics::GetGameInstance(aWorldContextObject));

	if (IsValid(gameInstance))
	{
		someOutputs = EConditionalOutput::Success;
	}
	else
	{
		someOutputs = EConditionalOutput::Failure;
	}
	return gameInstance;
}

bool UBG_Util::IsDebug(const UObject* aWorldContextObject, EBoolOutput& someOutputs, const bool anAdditionalCondition /* = true */)
{
	if (UBG_GameInstance* gameInstance = Cast<UBG_GameInstance>(UGameplayStatics::GetGameInstance(aWorldContextObject)))
	{
		if (gameInstance->IsDebug())
		{
			someOutputs = EBoolOutput::IsTrue;
		}
		else
		{
			someOutputs = EBoolOutput::IsFalse;
		}
		return gameInstance->IsDebug();
	}

	someOutputs = EBoolOutput::IsFalse;
	return false; // if no game instance, then we'll just say false. But there should always be a game instance when we call this, right?
}

void UBG_Util::QuitGameWithFade(const UObject* aWorldContextObject, float aFadeDuration, float aWaitAfterFadeDuration)
{
	if (APlayerCameraManager* camManager = UGameplayStatics::GetPlayerCameraManager(aWorldContextObject, 0))
	{
		//#CLOVE_NOTE: although we do want audio to fade out, this control doesn't seem to do it, so we'll have to manage FMOD audio fade ourselves
		camManager->StartCameraFade(0.0f, 1.0f, aFadeDuration, FLinearColor::Black, false /*shouldFadeAudio*/, true /*hold when finished*/);
	}

	if (aWorldContextObject)
	{
		if (UWorld* world = aWorldContextObject->GetWorld())
		{
			// #CLOVE_NOTE note that this timer won't work if global time dilation is set to 0 or something like that!
			FTimerHandle quitGameDummyHandle;
			world->GetTimerManager().SetTimer(quitGameDummyHandle, [aWorldContextObject]() 
				{
					if (APlayerController* playerController = UGameplayStatics::GetPlayerController(aWorldContextObject, 0))
					{
						playerController->ConsoleCommand("quit");
					}
				}, aFadeDuration + aWaitAfterFadeDuration, false /*loop*/);
		}
	}
}

void UBG_Util::TrackFPS_Trigger(const UObject* aWorldContextObject, const FOnFPSCalculatedSignature& anFPSCallback, FTimerHandle& aTimerHandle)
{

	TWeakObjectPtr<const UObject> contextObjectWeakPtr = aWorldContextObject;
	TrackFPS(contextObjectWeakPtr, anFPSCallback, aTimerHandle);

	UE_LOG(BG_UTIL_TICKING, Log, TEXT("Trigger TrackFPS"));
}

void UBG_Util::TrackFPS(const TWeakObjectPtr<const UObject> aWorldContextObject, const FOnFPSCalculatedSignature& anFPSCallback, FTimerHandle& aTimerHandle)
{
	if (aWorldContextObject.IsValid())
	{
		if (const UWorld* world = aWorldContextObject->GetWorld())
		{
			anFPSCallback.ExecuteIfBound(1.0f / world->GetDeltaSeconds());

			//UE_LOG(BG_UTIL_TICKING, Log, TEXT("Verify ticking in TrackFPS")); 

			aTimerHandle = world->GetTimerManager().SetTimerForNextTick([aWorldContextObject, anFPSCallback, world, &aTimerHandle]()
				{
					TrackFPS(aWorldContextObject, anFPSCallback, aTimerHandle);
				});
		}
	}
	else
	{
		UE_LOG(BG_UTIL_TICKING, Log, TEXT("Stop TrackFPS due to invalid aWorldContextObject"));
	}
}
