// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "MyPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include <Components/BoxComponent.h>
#include "RoadCollider.h"
#include "TrafficLight.h"
#include <Components/ArrowComponent.h>

// Sets default values
ACar::ACar()
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;
	mesh->SetCollisionProfileName(TEXT("Enemy"));
	mesh->SetGenerateOverlapEvents(true);

	frontCarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("FrontCarCollision"));
	frontCarCollision->SetupAttachment(mesh);
	destroyTime = 10.f;
	moveSpeed = 500.0f;
	damage = 10.f;
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ACar::OnOverlapBeginRoadCollision);
	frontCarCollision->OnComponentBeginOverlap.AddDynamic(this, &ACar::OnOverlapBeginFrontCar);
	frontCarCollision->OnComponentEndOverlap.AddDynamic(this, &ACar::OnOverlapEndFrontCar);

	int index = FMath::RandRange(0, 4);
	mesh->SetSkeletalMesh(meshList[index]);

	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, this, &ACar::CarDestroy, destroyTime, false);
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector P;
	FVector direction = GetActorForwardVector();
	FVector nowLocation = GetActorLocation();
	
	float speed;
	if (isStop) {
		speed = 0.0f;
		CheckTrafficLight();
	}
	else {
		if (isFrontCar)
			speed = 0.0f;
		else
			speed = moveSpeed;
	}

	P = nowLocation + (direction * speed * DeltaTime);
	
	//frontLeftTire->SetLocation(frontLeftTire->GetLocation() + (direction * -1));
	SetActorLocation(P);
}

void ACar::OnOverlapBeginRoadCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARoadCollider* roadCollider = Cast<ARoadCollider>(OtherActor);
	if (roadCollider) {
		float per = FMath::RandRange(0.0f, 1.0f);
		switch (roadCollider->turnDirection)
		{
		case ETurnDirection::TD_None:
			break;
		case ETurnDirection::TD_Left:
			if (roadCollider->turnPer)
			{
				FRotator rotator = GetActorRotation();
				rotator.Yaw = rotator.Yaw - 90.;
				SetActorRotation(rotator);
			}
			break;
		case ETurnDirection::TD_Right:
			if (roadCollider->turnPer)
			{
				UE_LOG(LogTemp, Warning, TEXT("%f / %f"), per, roadCollider->turnPer);
				FRotator rotator = GetActorRotation();
				rotator.Yaw = rotator.Yaw + 90.;
				SetActorRotation(rotator);
			}
			break;
		default:
			break;
		}
	}

	ATrafficLight* trafficLightCollider = Cast<ATrafficLight>(OtherActor);
	if (trafficLightCollider)
	{
		trafficLight = trafficLightCollider;
		CheckTrafficLight();
	}

	AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
	if (player)
	{
		player->GetDamaged(damage);
	}
}

void ACar::OnOverlapBeginFrontCar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
	ACar* frontCar = Cast<ACar>(OtherActor);
	if (frontCar)
		isFrontCar = true;
}

void ACar::OnOverlapEndFrontCar(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACar* frontCar = Cast<ACar>(OtherActor);
	if (frontCar) {
		// Delay 후 움직임
		FTimerHandle myTimerHandle;
		float delayTime = 0.5f;
		GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				isFrontCar = false;

				// 타이머 초기화
				GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
			}), delayTime, false); // 반복 실행을 하고 싶으면 false 대신 true 대입
	}
}

void ACar::CheckTrafficLight()
{
	if (trafficLight) {
		ETrafficLightType lightType = trafficLight->trafficLightType;
		switch (lightType)
		{
		case ETrafficLightType::TL_Green:
			isStop = false;
			break;
		case ETrafficLightType::TL_Yellow:
			isStop = true;
			break;
		case ETrafficLightType::TL_Red:
			isStop = true;
			break;
		default:
			break;
		}
	}
}

void ACar::CarDestroy()
{
	Destroy();
}

