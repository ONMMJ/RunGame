// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapManager.generated.h"

class AMapController;
class ASpawner;

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
	UPROPERTY(VisibleAnywhere, blueprintReadOnly, Category = "MoveInfo")
	bool isStart;



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
	UPROPERTY(VisibleAnywhere, Category = "MapEffect")
	TArray<AActor*> allEffectList;
	UPROPERTY(EditAnywhere, Category = "MapEffect")
	TArray<AActor*> snowEffectList;

	// map Spawner
	UPROPERTY(VisibleAnywhere, Category = "MapSpawner")
	TArray<ASpawner*> allSpawnerList;
	UPROPERTY(EditAnywhere, Category = "MapSpawner")
	TArray<ASpawner*> normalSpawnerList;
	UPROPERTY(EditAnywhere, Category = "MapSpawner")
	TArray<ASpawner*> snowSpawnerList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// BindFunction
	void ChangedMapType(AMapController* mapController);

	// map Effect
	void setMapEffect(EMapType mapType);
	void AddEffectList(TArray<AActor*> addList);
	void allOffMapEffect();
	void onMapEffect(TArray<AActor*> effectList);

	// map Spawner
	void setMapSpawner(EMapType mapType);
	void AddSpawnerList(TArray<ASpawner*> addList);
	void allOffMapSpawner();
	void onMapSpawner(TArray<ASpawner*> spawnerList);

	void AddSwitchMapType(AMapController* map);

	// speed
	void SetSpeed(float speed);
	void AddSpeed(float add);
	void AddSpeedBuff(float buff);
	void SetMapSpeedBuff(float buff);


	UFUNCTION(BlueprintCallable)
	void SetPlayerDamaged(bool isDamaged);
	UFUNCTION(BlueprintCallable)
	void Gameover();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CalTotalSpeed();

	void SetNextMapType();

	UFUNCTION()
	AMapController* GetMap(EMapType mapType, EMapLoopType mapLoopType);
};
