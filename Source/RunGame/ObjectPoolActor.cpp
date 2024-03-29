// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolActor.h"

// Sets default values
AObjectPoolActor::AObjectPoolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectPoolActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectPoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectPoolActor::SetActive(bool isActive)
{
	SetActorHiddenInGame(!isActive);
}

