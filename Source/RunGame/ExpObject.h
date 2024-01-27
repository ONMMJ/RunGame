// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorMovingOnFloor.h"
#include "ExpObject.generated.h"

UCLASS()
class RUNGAME_API AExpObject : public AActorMovingOnFloor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExpObject();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float exp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetActive(bool isActive);

};
