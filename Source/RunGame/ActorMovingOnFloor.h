// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolActor.h"
#include "ActorMovingOnFloor.generated.h"

UCLASS()
class RUNGAME_API AActorMovingOnFloor : public AObjectPoolActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorMovingOnFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void AttachFloor();
	void DetachFloor();

public:

	virtual void SetActive(bool isActive) override;
};
