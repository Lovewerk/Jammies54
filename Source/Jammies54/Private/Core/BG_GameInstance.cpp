// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BG_GameInstance.h"

bool UBG_GameInstance::IsDebug() const
{
#if UE_BUILD_SHIPPING
	return false;
#else
	return bDebugMode;
#endif
}
