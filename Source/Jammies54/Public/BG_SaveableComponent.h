// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Saving/BG_Identifiable.h"
#include <Core/BG_GameData.h>
#include "BG_SaveableComponent.generated.h"

class UBG_SaveGameBase;

//COMMENT ABOVE DELEGATE DECLARATION
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeforeSerialize, UBG_SaveableComponent*, aSaveComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAfterDeserialize, UBG_SaveableComponent*, aSaveComponent);

UCLASS( Blueprintable, ClassGroup=(Saving), meta=(BlueprintSpawnableComponent) )
class JAMMIES54_API UBG_SaveableComponent : public UActorComponent, public IBG_Identifiable
{
	GENERATED_BODY()

	// used as this object's key for saving. #CLOVE_TODO: Add some validation to ensure these are not getting changed unexpectedly?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FGuid myGuid;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FBG_SaveableData myCurrentData;

public:	
	// Sets default values for this component's properties
	UBG_SaveableComponent();

	virtual void InitializeComponent() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Comment about UPROPERTY
	UPROPERTY(BlueprintAssignable)
		FOnBeforeSerialize myOnBeforeSerializeDelegate;
	UPROPERTY(BlueprintAssignable)
		FOnAfterDeserialize myOnAfterDeserializeDelegate;

	void HandleSaveStarted(UBG_SaveGameBase* aSaveGame);
	// void HandleSaveCompleted() const;
	// void HandleLoadStarted() const;
	void HandleLoadCompleted(const UBG_SaveGameBase* aSaveGame);

public:
	FGuid GetGuid_Implementation() override;
	void SetGuid_Implementation(const FGuid& aGuid) override;
};
