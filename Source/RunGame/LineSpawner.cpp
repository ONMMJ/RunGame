// Fill out your copyright notice in the Description page of Project Settings.


#include "LineSpawner.h"

// Sets default values
ALineSpawner::ALineSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spawnTime = 1.f;
	isLinked = false;

	// linkOption
	linkMoveSpeed = 3.f;
	isTurn = true;
	moveTurnMinTime = 3.f;
	moveTurnMaxTime = 10.f;
}

// Called when the game starts or when spawned
void ALineSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (isLinked)
	{
		nowMoveTurnTime = 0.f;
		nextMoveTurnTime = FMath::RandRange(moveTurnMinTime, moveTurnMaxTime);
		moveVector = end->GetActorLocation() - start->GetActorLocation();
		moveVector.Normalize();
		moveDirection = 1;

		GetWorldTimerManager().SetTimer(timerHandle, this, &ALineSpawner::LinkedSpawn, spawnTime, true);
	}
	else
	{
		GetWorldTimerManager().SetTimer(timerHandle, this, &ALineSpawner::RandomSpawn, spawnTime, true);
	}
}

void ALineSpawner::Tick(float DeltaTime)
{
	if (isLinked)
	{
		nowMoveTurnTime += DeltaTime;
		if (nowMoveTurnTime >= nextMoveTurnTime)
		{
			if (moveDirection == 0)
			{
				moveDirection = FMath::RandRange(0, 1) ? -1 : 1;
				nextMoveTurnTime = FMath::RandRange(moveTurnMinTime, moveTurnMaxTime);
			}
			else
			{
				moveDirection = 0;
				nextMoveTurnTime = 1.f;
			}
			nowMoveTurnTime = 0.f;
		}
		move->SetActorLocation(move->GetActorLocation() + (moveVector * moveDirection * linkMoveSpeed));
		if (move->GetActorLocation().Y <= start->GetActorLocation().Y)
			moveDirection *= -1;
		else if (move->GetActorLocation().Y >= end->GetActorLocation().Y)
			moveDirection *= -1;
	}
}

void ALineSpawner::RandomSpawn()
{
		UWorld* world = GetWorld();
		FRotator rotator = FRotator::ZeroRotator;
		FVector spawnLocation;
		FVector startPos = start->GetActorLocation();
		FVector endPos = end->GetActorLocation();

		spawnLocation.X = FMath::RandRange(startPos.X, endPos.X);
		spawnLocation.Y = FMath::RandRange(startPos.Y, endPos.Y);
		spawnLocation.Z = FMath::RandRange(startPos.Z, endPos.Z);

		world->SpawnActor<AActor>(spawnActor, spawnLocation, rotator);
}

void ALineSpawner::LinkedSpawn()
{
		UWorld* world = GetWorld();
		FRotator rotator = FRotator::ZeroRotator;
		FVector spawnLocation = move->GetActorLocation();

		world->SpawnActor<AActor>(spawnActor, spawnLocation, rotator);
}
