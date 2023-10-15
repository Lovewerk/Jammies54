// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_SaveGameBase.h"

UBG_SaveGameBase::UBG_SaveGameBase()
{
	SetNameAndUserIndex(mySaveSlotName, mySaveUserIndex);
	//myGameData = CreateDefaultSubobject<UBG_GameData>("GameData");
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

FBG_GameData& UBG_SaveGameBase::GetGameData()
{
	return myGameData;
}
