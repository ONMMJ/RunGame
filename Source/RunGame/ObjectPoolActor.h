// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPool.h"
#include "ObjectPoolActor.generated.h"

UCLASS()
class RUNGAME_API AObjectPoolActor : public AActor, public IObjectPool
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectPoolActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void SetActive(bool isActive) override;
};
