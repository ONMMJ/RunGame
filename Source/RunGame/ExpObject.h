// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorMovingOnFloor.h"
#include "ExpObject.generated.h"

UCLASS()
class RUNGAME_API AExpObject : public AActorMovingOnFloor
{
	GENERATED_BODY()
	
	UPROPERTY()
	bool isTargetting;
public:	
	// Sets default values for this actor's properties
	AExpObject();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* staticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float exp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TargetInfo")
	AActor* target;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TargetInfo")
	float moveSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetActive(bool isActive);
	void TrackingPlayer(AActor* actor);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
