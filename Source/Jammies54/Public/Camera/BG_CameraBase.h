// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CinematicCamera/Public/CineCameraActor.h"
#include "BG_CameraBase.generated.h"

UCLASS()
class JAMMIES54_API ABG_CameraBase : public ACineCameraActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABG_CameraBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
