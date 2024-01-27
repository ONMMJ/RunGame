// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawner.h"

// Sets default values
AActorSpawner::AActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	spawnTime = 3.f;
}

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(timerHandle, this, &AActorSpawner::SpawnActor, spawnTime, true);
}

void AActorSpawner::SpawnActor()
{
	UWorld* world = GetWorld();
	int index = FMath::RandRange(0, spawnPointList.Num() - 1);
	FRotator rotator = spawnPointList[index]->GetActorRotation();
	FVector spawnLocation = spawnPointList[index]->GetActorLocation();

	AActor* actor = world->SpawnActor<AActor>(spawnActor, spawnLocation, rotator);
}