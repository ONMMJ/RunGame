// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapManager.generated.h"

class AMapController;

USTRUCT()
struct FMapWaitingList
{
	GENERATED_BODY()

public:
	// Waiting Map List Start
	UPROPERTY(VisibleAnywhere)
	TArray<AMapController*> start;

	UPROPERTY(VisibleAnywhere)
	TArray<AMapController*> loop;
};

USTRUCT(BlueprintType)
struct FMoveMap
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	AActor* parent;

	UPROPERTY(VisibleAnywhere)
	AMapController* child;
};

UCLASS()
class RUNGAME_API AMapManager : public AActor
{
	GENERATED_BODY()

	// Waiting Map List
	UPROPERTY(VisibleAnywhere)
	FMapWaitingList normalMapList;

	UPROPERTY(VisibleAnywhere)
	FMapWaitingList snowMapList;

	UPROPERTY(VisibleAnywhere)
	FMapWaitingList upStairMapList;

	UPROPERTY()
	bool isPlayerDamaged;
public:	
	// Sets default values for this actor's properties
	AMapManager();

	UPROPERTY(VisibleAnyWhere)
	EMapType nextMapType;
	UPROPERTY(VisibleAnyWhere)
	EMapLoopType nextMapLoopType;

	// move Info
	UPROPERTY(EditAnywhere, blueprintReadOnly, Category = "MoveInfo")
	FVector direction;
	UPROPERTY(EditAnywhere, blueprintReadOnly, Category = "MoveInfo")
	float speed;
	UPROPERTY(EditAnywhere, blueprintReadOnly, Category = "MoveInfo")
	float playerDamagedSpeed;
	UPROPERTY(VisibleAnywhere, blueprintReadOnly, Category = "MoveInfo")
	float mapSpeedBuff;
	UPROPERTY(VisibleAnywhere, blueprintReadOnly, Category = "MoveInfo")
	float speedBuff;

	UPROPERTY(VisibleAnywhere, blueprintReadOnly, Category = "MoveInfo")
	float totalSpeed;



	// map Info
	UPROPERTY(EditAnywhere, blueprintReadOnly, Category = "MapInfo")
	float nextMapTypeTime;



	// map List
	UPROPERTY(EditAnywhere, Category = "MapList")
	FMoveMap moveActorList[3];

	UPROPERTY(EditAnywhere, Category = "MapList")
	AActor* waitingMapParentActor;

	UPROPERTY(EditAnywhere, blueprintReadOnly, Category = "MapList")
	TArray<TSubclassOf<AMapController>> allMapList;

	// map Effect
	UPROPERTY(EditAnywhere, Category = "MapList")
	TArray<AActor*> snowEffectList;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddSwitchMapType(AMapController* map);
	void SetSpeed(float speed);
	void AddSpeed(float add);
	void AddSpeedBuff(float buff);
	void RemoveSpeedBuff(float buff);
	void SetPlayerDamaged(bool isDamaged);
	void SetNextMapType();

	UFUNCTION()
	AMapController* GetMap(EMapType mapType, EMapLoopType mapLoopType);
};
