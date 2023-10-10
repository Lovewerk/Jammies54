// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Saving/BG_Identifiable.h"
#include "BG_SaveableComponent.generated.h"

class UBG_SaveGameBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHandleSaveStartedSignature, UBG_SaveGameBase*, aSaveGame); // non-const because the save-game is meant to be modified on save begin
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHandleSaveCompletedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHandleLoadStartedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHandleLoadCompletedSignature, const UBG_SaveGameBase*, aSaveGame);

UCLASS( Blueprintable, ClassGroup=(Saving), meta=(BlueprintSpawnableComponent) )
class JAMMIES54_API UBG_SaveableComponent : public UActorComponent, public IBG_Identifiable
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FGuid myGuid; // used as this object's key for saving

public:	
	// Sets default values for this component's properties
	UBG_SaveableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
		FHandleSaveStartedSignature mySaveStartedDelegate;
	UPROPERTY(BlueprintAssignable)
		FHandleSaveCompletedSignature mySaveCompletedDelegate;
	UPROPERTY(BlueprintAssignable)
		FHandleLoadStartedSignature myLoadStartedDelegate;
	UPROPERTY(BlueprintAssignable)
		FHandleLoadCompletedSignature myLoadCompletedDelegate;

	void HandleSaveStarted(UBG_SaveGameBase* aSaveGame);
	void HandleSaveCompleted() const;
	void HandleLoadStarted() const;
	void HandleLoadCompleted(const UBG_SaveGameBase* aSaveGame) const;

public:
	FGuid GetGuid_Implementation() override;
	void SetGuid_Implementation(const FGuid& aGuid) override;
};
