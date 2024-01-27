// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LineSpawner.generated.h"

UCLASS()
class RUNGAME_API ALineSpawner : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY()
	FVector moveVector;
	UPROPERTY()
	int moveDirection;
	UPROPERTY()
	float nowMoveTurnTime;
	UPROPERTY()
	float nextMoveTurnTime;
	UPROPERTY()
	FTimerHandle timerHandle;
public:	
	// Sets default values for this actor's properties
	ALineSpawner();

	UPROPERTY(EditAnywhere, category = "SpawnPosition")
	AActor* start;

	UPROPERTY(EditAnywhere, category = "SpawnPosition")
	AActor* end;	

	UPROPERTY(EditAnywhere, category = "SpawnPosition")
	AActor* move;


	UPROPERTY(EditAnywhere, category = "SpawnInfo")
	TSubclassOf<AActor> spawnActor; 
	UPROPERTY(EditAnywhere, category = "SpawnInfo")
	float spawnTime;
	UPROPERTY(EditAnywhere, category = "SpawnInfo")
	bool isLinked;
	UPROPERTY(EditAnywhere, category = "SpawnLinkedOption")
	float linkMoveSpeed;
	UPROPERTY(EditAnywhere, category = "SpawnLinkedOption")
	bool isTurn;
	UPROPERTY(EditAnywhere, category = "SpawnLinkedOption")
	float moveTurnMinTime;
	UPROPERTY(EditAnywhere, category = "SpawnLinkedOption")
	float moveTurnMaxTime;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RandomSpawn();
	void LinkedSpawn();
};
