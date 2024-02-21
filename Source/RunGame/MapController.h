// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapController.generated.h"

class AExpObject;

UENUM(BlueprintType)
enum class EMapType : uint8
{
	MT_Normal UMETA(DisplayName = "Normal"),
	MT_Snow UMETA(DisplayName = "Snow"),
	MT_Num UMETA(DisplayName = "Num"),
};

UENUM(BlueprintType)
enum class EMapLoopType : uint8
{
	MLT_Start UMETA(DisplayName = "Start"),
	MLT_Loop UMETA(DisplayName = "Loop"),
};

UCLASS()
class RUNGAME_API AMapController : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	class UStaticMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* startBoxComponent;
public:	
	// Sets default values for this actor's properties
	AMapController();

	// MapManager
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MapInfo")
	class AMapManager* mapManager;
	// MapInfo
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapInfo")
	EMapType mapType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapInfo")
	EMapLoopType mapLoopType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapInfo")
	float speedBuff;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void OnOverlapBeginPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetActive(bool isActive);
};
