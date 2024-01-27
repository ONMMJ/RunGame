// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawner.generated.h"

UCLASS()
class RUNGAME_API AActorSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	FTimerHandle timerHandle;
public:	
	// Sets default values for this actor's properties
	AActorSpawner();

	UPROPERTY(EditAnywhere, category = "SpawnInfo")
	TArray<AActor*> spawnPointList;

	UPROPERTY(EditAnywhere, category = "SpawnInfo")
	TSubclassOf<AActor> spawnActor;

	UPROPERTY(EditAnywhere, category = "SpawnInfo")
	float spawnTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void SpawnActor();
};
