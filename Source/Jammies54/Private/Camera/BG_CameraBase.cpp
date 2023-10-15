// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/BG_CameraBase.h"

// Sets default values
ABG_CameraBase::ABG_CameraBase(const FObjectInitializer& ObjectInitializer)
	: ACineCameraActor(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABG_CameraBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABG_CameraBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

