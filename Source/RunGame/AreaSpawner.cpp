// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaSpawner.h"

AAreaSpawner::AAreaSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAreaSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AAreaSpawner::Spawn()
{
	UWorld* world = GetWorld();
	FRotator rotator = start->GetActorRotation();
	FVector spawnLocation;
	FVector startPos = start->GetActorLocation();
	FVector endPos = end->GetActorLocation();

	spawnLocation.X = FMath::RandRange(startPos.X, endPos.X);
	spawnLocation.Y = FMath::RandRange(startPos.Y, endPos.Y);
	spawnLocation.Z = FMath::RandRange(startPos.Z, endPos.Z);

	AObjectPoolActor* object = GetObjectFromPool(spawnLocation, rotator);
}
