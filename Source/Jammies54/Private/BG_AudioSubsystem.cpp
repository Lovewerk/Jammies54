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
	return pow(10.0f, aDB / 10.0f);
}

float UBG_AudioSubsystem::LinearTodB(float aLinear)
{
	return 10.0f * log10(aLinear); //#CLOVE_CHECK: ensure these formulae are correct
}

void UBG_AudioSubsystem::SetVCAVolume(const EVCAName aVCAName, const float& aLinearVolume)
{
	FString VCAName = "vca:/" + GetVCAName(aVCAName);

	if (myStudioSystem)
	{
		FMOD::Studio::VCA* vca{nullptr};
		myStudioSystem->getVCA(TCHAR_TO_UTF8(*VCAName), &vca);
		if (vca && vca->isValid())
		{
			vca->setVolume(aLinearVolume);
			UE_LOG(BG_AUDIO_SYSTEM, Log, TEXT("Setting %s volume to %d"), *VCAName, aLinearVolume);
		}
		else
		{
			UE_LOG(BG_AUDIO_SYSTEM, Warning, TEXT("Unable to set volume on %s as it is null"), *VCAName);
		}
	}
	else
	{
		UE_LOG(BG_AUDIO_SYSTEM, Warning, TEXT("Unable to set volume on %s as the studio system is null"), *VCAName);
	}
}

float UBG_AudioSubsystem::GetVCAVolumeLinear(const EVCAName aVCAName)
{
	FString VCAName = "vca:/" + GetVCAName(aVCAName);

	if (myStudioSystem)
	{
		FMOD::Studio::VCA* vca{nullptr};
		myStudioSystem->getVCA(TCHAR_TO_UTF8(*VCAName), &vca);
		if (vca && vca->isValid())
		{
			float volume;
			vca->getVolume(&volume);
			if (volume)
			{
				UE_LOG(BG_AUDIO_SYSTEM, Log, TEXT("VCA %s volume: %d"), *VCAName, volume);
				return volume;
			}
			{
				UE_LOG(BG_AUDIO_SYSTEM, Warning, TEXT("VCA %s volume result was null"), *VCAName);
			}
		}
		else
		{
			UE_LOG(BG_AUDIO_SYSTEM, Warning, TEXT("Unable to get volume from %s as it is null or invalid"), *VCAName);
		}
	}
	else
	{
		UE_LOG(BG_AUDIO_SYSTEM, Warning, TEXT("Unable to get volume of %s as the studio system is null"), *VCAName);
	}
	return 0;
}

FString UBG_AudioSubsystem::GetVCAName(const EVCAName aVCA) const
{
	//return UEnum::GetValueAsString(aVCA); // result: EVCAName::name
	return UBG_Util::EnumToString<EVCAName>(aVCA); // result: name
}
