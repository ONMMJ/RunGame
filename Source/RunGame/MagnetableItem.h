// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorMovingOnFloor.h"
#include "MagnetableInterface.h"
#include "MagnetableItem.generated.h"

UCLASS()
class RUNGAME_API AMagnetableItem : public AActorMovingOnFloor, public IMagnetableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagnetableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TargetInfo")
	AActor* target;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TargetInfo")
	float moveSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// IMagnetableInterface을(를) 통해 상속됨
	virtual void Targetting_Implementation(AActor* target) override;

};
