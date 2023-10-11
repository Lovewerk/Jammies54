// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_SaveGameBase.h"

UBG_SaveGameBase::UBG_SaveGameBase()
{
	SetNameAndUserIndex(mySaveSlotName, mySaveUserIndex);

	myGameData = NewObject<UBG_GameData>();
}

FString UBG_SaveGameBase::GetSaveSlotName()
{
	return mySaveSlotName;
}

int32 UBG_SaveGameBase::GetSaveUserIndex()
{
	return mySaveUserIndex;
}

int32 UBG_SaveGameBase::GetSaveVersion() const
{
	return mySaveVersion;
}

void UBG_SaveGameBase::SetNameAndUserIndex(const FString& aSlotName, const int32 aUserIndex)
{
	mySaveSlotName = TEXT("%s"),aSlotName;
	mySaveUserIndex = aUserIndex;
}

UBG_GameData* UBG_SaveGameBase::GetGameData()
{
	return myGameData;
}

UBG_LevelData* UBG_SaveGameBase::GetLevelData()
{
	return IsValid(myGameData) ? myGameData->myLevelData : nullptr;
}

UBG_PlayerData* UBG_SaveGameBase::GetPlayerData()
{
	return IsValid(myGameData) ? myGameData->myPlayerData : nullptr;
}
