// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorMovingOnFloor.h"
#include "EnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API AEnemyAttack : public AActorMovingOnFloor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyAttack();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	class UCapsuleComponent* damageArea;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "AttackInfo")
	float beforeDelayTime;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "AttackInfo")
	float afterDelayTime;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "AttackInfo")
	float damage;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
};
