// Fill out your copyright notice in the Description page of Project Settings.


#include "LineSpawner.h"

// Sets default values
ALineSpawner::ALineSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	// linkOption
	spawnPointSpeed = 3.f;
	YMoveTurnMinTime = 3.f;
	YMoveTurnMaxTime = 10.f;
}

// Called when the game starts or when spawned
void ALineSpawner::BeginPlay()
{
	Super::BeginPlay();
	nowYMoveTurnTime = 0.f;
	nextYMoveTurnTime = FMath::RandRange(YMoveTurnMinTime, YMoveTurnMaxTime);
	nowZMoveTurnTime = 0.f;
	nextZMoveTurnTime = FMath::RandRange(ZMoveTurnMinTime, ZMoveTurnMaxTime);
	YMoveDirection = 1;
	ZMoveDirection = 0;
}

void ALineSpawner::Tick(float DeltaTime)
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
	if (spawnPoint->GetActorLocation().Y <= start->GetActorLocation().Y)
		YMoveDirection *= -1;
	else if (spawnPoint->GetActorLocation().Y >= end->GetActorLocation().Y)
		YMoveDirection *= -1;

	if (spawnPoint->GetActorLocation().Z <= start->GetActorLocation().Z)
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
	else if (spawnPoint->GetActorLocation().Z >= end->GetActorLocation().Z)
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
	spawnPoint->SetActorLocation(spawnPoint->GetActorLocation() + (FVector::RightVector * YMoveDirection * spawnPointSpeed) + (FVector::UpVector * ZMoveDirection * spawnPointSpeed));
	
}

void ALineSpawner::Spawn()
{
		UWorld* world = GetWorld();
		FRotator rotator = FRotator::ZeroRotator;
		FVector spawnLocation = spawnPoint->GetActorLocation();

		AObjectPoolActor* object = GetObjectFromPool(spawnLocation, rotator);
}
