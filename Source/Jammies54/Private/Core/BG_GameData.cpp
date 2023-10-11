// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BG_GameData.h"

UBG_GameData::UBG_GameData()
{
	myLevelData = NewObject<UBG_LevelData>();
	myPlayerData = NewObject<UBG_PlayerData>();
}
