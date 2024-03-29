// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "ObjectPoolActor.h"

// Sets default values
ASpawner::ASpawner()
{
	spawnTime = 1.f;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(timerHandle, this, &ASpawner::Spawn, spawnTime, true);	

    for (int32 i = 0; i < poolSize; i++)
    {
        AObjectPoolActor* spawnObject = GetWorld()->SpawnActor<AObjectPoolActor>(spawnActor, FVector::ZeroVector, FRotator::ZeroRotator);
        if (spawnObject)
        {
            spawnObject->SetActive(false);
            objectPool.Add(spawnObject);
        }
    }
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::StartSpawn()
{
	GetWorldTimerManager().UnPauseTimer(timerHandle);
}

void ASpawner::PauseSpawn()
{
	GetWorldTimerManager().PauseTimer(timerHandle);
}

AObjectPoolActor* ASpawner::GetObjectFromPool(FVector spawnPosition, FRotator spawnRotator)
{
    UE_LOG(LogTemp, Error, TEXT("aaaaaaaaaaaaaaaaaaaaaaaa"));
    for (AObjectPoolActor* object : objectPool)
    {
        if (object->IsHidden())
        {
            object->SetActorLocation(spawnPosition);
            object->SetActorRotation(spawnRotator);
            object->SetActive(true);
            return object;
        }
    }

    return nullptr;
}


