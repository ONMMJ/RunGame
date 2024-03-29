// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class AObjectPoolActor;

UCLASS(Abstract)
class RUNGAME_API ASpawner : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FTimerHandle timerHandle;

	TArray<AObjectPoolActor*> objectPool;
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(EditAnywhere, category = "SpawnInfo")
	TSubclassOf<AActor> spawnActor;
	UPROPERTY(EditAnywhere, category = "SpawnInfo")
	float spawnTime;
	UPROPERTY(EditAnywhere, category = "SpawnInfo")
	int32 poolSize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Spawn() PURE_VIRTUAL(ASpawner::Spawn, );

	void StartSpawn();
	void PauseSpawn();
	AObjectPoolActor* GetObjectFromPool(FVector spawnPosition, FRotator spawnRotator);
};
