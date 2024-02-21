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
	YMoveTurnMinTime = 3.f;
	YMoveTurnMaxTime = 10.f;
}

// Called when the game starts or when spawned
void ALineSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (isLinked)
	{
		nowYMoveTurnTime = 0.f;
		nextYMoveTurnTime = FMath::RandRange(YMoveTurnMinTime, YMoveTurnMaxTime);
		nowZMoveTurnTime = 0.f;
		nextZMoveTurnTime = FMath::RandRange(ZMoveTurnMinTime, ZMoveTurnMaxTime);
		YMoveDirection = 1;
		ZMoveDirection = 0;


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
		nowYMoveTurnTime += DeltaTime;
		nowZMoveTurnTime += DeltaTime;
		if (nowYMoveTurnTime >= nextYMoveTurnTime)
		{
			if (YMoveDirection == 0)
			{
				YMoveDirection = FMath::RandRange(0, 1) ? -1 : 1;
				nextYMoveTurnTime = FMath::RandRange(YMoveTurnMinTime, YMoveTurnMaxTime);
			}
			else
			{
				YMoveDirection = 0;
				nextYMoveTurnTime = 1.f;
			}
			nowYMoveTurnTime = 0.f;
		}
		if (move->GetActorLocation().Y <= start->GetActorLocation().Y)
			YMoveDirection *= -1;
		else if (move->GetActorLocation().Y >= end->GetActorLocation().Y)
			YMoveDirection *= -1;

		if (move->GetActorLocation().Z <= start->GetActorLocation().Z)
		{
			if (FMath::RandRange(0, 1)) 
			{
				ZMoveDirection = 0;
			}
			else
			{
				ZMoveDirection *= -1;
			}
		}
		else if (move->GetActorLocation().Z >= end->GetActorLocation().Z)
			ZMoveDirection *= -1;

		if (nowZMoveTurnTime >= nextZMoveTurnTime)
		{
			if (ZMoveDirection == 0)
			{
				ZMoveDirection = 1;
				nextZMoveTurnTime = FMath::RandRange(ZMoveTurnMinTime, ZMoveTurnMaxTime);
			}
			nowZMoveTurnTime = 0.f;

		}

		//UE_LOG(LogTemp, Warning, TEXT("%d ,%f"), ZMoveDirection, nextZMoveTurnTime);
		move->SetActorLocation(move->GetActorLocation() + (FVector::RightVector * YMoveDirection * linkMoveSpeed) + (FVector::UpVector * ZMoveDirection * linkMoveSpeed));
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
