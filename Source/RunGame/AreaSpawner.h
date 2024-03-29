// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawner.h"
#include "AreaSpawner.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API AAreaSpawner : public ASpawner
{
	GENERATED_BODY()

	UPROPERTY()
	bool isTargetting;
public:
	// Sets default values for this actor's properties
	AAreaSpawner();
	UPROPERTY(EditAnywhere, category = "SpawnPosition")
	AActor* start;

	UPROPERTY(EditAnywhere, category = "SpawnPosition")
	AActor* end;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Spawn() override;
};
