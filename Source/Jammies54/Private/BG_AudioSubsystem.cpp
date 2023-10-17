#include "BG_AudioSubsystem.h"

#include "../Jammies54.h"

#include "fmod_studio.hpp"
#include "FMODStudioModule.h"
#include "Core/BG_Util.h"


void UBG_AudioSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

	if (IFMODStudioModule::IsAvailable())
	{
		myStudioSystem = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);
	}
	else
	{
		UE_LOG(BG_AUDIO_SYSTEM, Log, TEXT("FMOD Studio Module unavailable"));
	}
	
	SetVCAVolume(EVCAName::Music, 0.0f);

	UE_LOG(BG_AUDIO_SYSTEM, Log, TEXT("AudioSubsystem Initialized!"));
}

float UBG_AudioSubsystem::dBToLinear(float aDB)
{
	return pow(10.0f, aDB / 20.0f); // verify this is correct
}

void UBG_AudioSubsystem::SetVCAVolume(const EVCAName aVCAName, const float& aLinearVolume)
{
	FString VCAName = "vca:/" + GetVCAName(aVCAName);

	if (myStudioSystem)
	{
		FMOD::Studio::VCA* Vca{nullptr};
		myStudioSystem->getVCA(TCHAR_TO_UTF8(*VCAName), &Vca);
		if (Vca)
		{
			Vca->setVolume(aLinearVolume);
			UE_LOG(BG_AUDIO_SYSTEM, Log, TEXT("Setting %s volume to %d"), *VCAName, aLinearVolume);
		}
		else
		{
			UE_LOG(BG_AUDIO_SYSTEM, Log, TEXT("Unable to set volume on %s as it is null"), *VCAName);
		}
	}
	else
	{
		UE_LOG(BG_AUDIO_SYSTEM, Log, TEXT("Unable to set volume on %s as the studio system is null"), *VCAName);
	}
	

}

FString UBG_AudioSubsystem::GetVCAName(const EVCAName aVCA) const
{

	//return UEnum::GetValueAsString(aVCA); // result: EVCAName::name
	return UBG_Util::EnumToString<EVCAName>(aVCA); // result: name
}
