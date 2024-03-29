// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawner.h"
#include "LineSpawner.generated.h"

UCLASS()
class RUNGAME_API ALineSpawner : public ASpawner
{
	GENERATED_BODY()
	
	UPROPERTY()
	int YMoveDirection;
	UPROPERTY()
	float nowYMoveTurnTime;
	UPROPERTY()
	float nextYMoveTurnTime;


	int ZMoveDirection;
	UPROPERTY()
	float nowZMoveTurnTime;
	UPROPERTY()
	float nextZMoveTurnTime;
public:	
	// Sets default values for this actor's properties
	ALineSpawner();

	UPROPERTY(EditAnywhere, category = "SpawnPosition")
	AActor* start;

	UPROPERTY(EditAnywhere, category = "SpawnPosition")
	AActor* end;	

	UPROPERTY(EditAnywhere, category = "SpawnPosition")
	AActor* spawnPoint;

	UPROPERTY(EditAnywhere, category = "SpawnLinkedOption")
	float spawnPointSpeed;
	UPROPERTY(EditAnywhere, category = "SpawnLinkedOption")
	float YMoveTurnMinTime;
	UPROPERTY(EditAnywhere, category = "SpawnLinkedOption")
	float YMoveTurnMaxTime;
	UPROPERTY(EditAnywhere, category = "SpawnLinkedOption")
	float ZMoveTurnMinTime;
	UPROPERTY(EditAnywhere, category = "SpawnLinkedOption")
	float ZMoveTurnMaxTime;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Spawn() override;
};
