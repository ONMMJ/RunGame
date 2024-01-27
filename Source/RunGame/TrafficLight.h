// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficLight.generated.h"


UENUM(BlueprintType)
enum class ETrafficLightType : uint8
{
	TL_Green UMETA(DisplayName = "GreanLight"),
	TL_Yellow UMETA(DisplayName = "YellowLight"),
	TL_Red UMETA(DisplayName = "RedLight"),
};

UCLASS()
class RUNGAME_API ATrafficLight : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnyWhere)
	UMaterialInstanceDynamic* DynamicMaterialMesh;

public:	
	// Sets default values for this actor's properties
	ATrafficLight();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* StaticMaterialMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	ETrafficLightType trafficLightType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* boxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightTexture")
	UTexture* greenLightTexture;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightTexture")
	UTexture* yellowLightTexture;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightTexture")
	UTexture* redLightTexture;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	float nowTime;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float greenLightTime;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float yellowLightTime;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float redLightTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLight(UTexture* texture);
};
