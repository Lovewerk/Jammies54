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

bool UBG_Util::IsDebug(const UObject* aWorldContextObject, const bool anAdditionalCondition)
{
	if (UBG_GameInstance* gameInstance = Cast<UBG_GameInstance>(UGameplayStatics::GetGameInstance(aWorldContextObject)))
	{
		return gameInstance->IsDebug();
	}
	return false; // if no game instance, then we'll just say false. But there should always be a game instance when we call this, right?
}
