#include "Core/BG_Util.h"
#include "Kismet/GameplayStatics.h"

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
				}, aFadeDuration, false /*loop*/);

			if (UGameViewportClient* ViewportClient = world->GetGameViewport())
			{
				ViewportClient->RemoveAllViewportWidgets();
			}
		}

		// #CLOVE_TODO: Add a way to have all widgets on screen fade out as we fade to black
	}
}
