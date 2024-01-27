// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficLight.h"
#include "Components/StaticMeshComponent.h"
#include <Components/BoxComponent.h>

// Sets default values
ATrafficLight::ATrafficLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMaterialMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DynamicMaterialMesh"));
	if (StaticMaterialMesh)
	{
		RootComponent = StaticMaterialMesh;
	}

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	if (boxComponent) {
		boxComponent->SetupAttachment(StaticMaterialMesh);
		boxComponent->SetCollisionProfileName(TEXT("RoadCollision"));
		boxComponent->SetRelativeLocation(FVector(1230.f, 600.f, 60.f));
	}
}

// Called when the game starts or when spawned
void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();

	DynamicMaterialMesh = StaticMaterialMesh->CreateDynamicMaterialInstance(0);

	nowTime = 0.0f;
}

// Called every frame
void ATrafficLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	nowTime += DeltaTime;

	switch (trafficLightType)
	{
	case ETrafficLightType::TL_Green:
		if (nowTime >= greenLightTime)
		{
			trafficLightType = ETrafficLightType::TL_Yellow;
			nowTime = 0;
			SetLight(yellowLightTexture);
		}
		break;
	case ETrafficLightType::TL_Yellow:
		if (nowTime >= yellowLightTime)
		{
			trafficLightType = ETrafficLightType::TL_Red;
			nowTime = 0;
			SetLight(redLightTexture);
		}
		break;
	case ETrafficLightType::TL_Red:
		if (nowTime >= redLightTime)
		{
			trafficLightType = ETrafficLightType::TL_Green;
			nowTime = 0;
			SetLight(greenLightTexture);
		}
		break;
	default:
		break;
	}
}

void ATrafficLight::SetLight(UTexture* texture)
{
	if(DynamicMaterialMesh)
		DynamicMaterialMesh->SetTextureParameterValue(FName("T_Light"), texture);
}

