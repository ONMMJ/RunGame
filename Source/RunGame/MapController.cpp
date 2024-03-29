// Fill out your copyright notice in the Description page of Project Settings.


#include "MapController.h"
#include <Components/BoxComponent.h>

// Sets default values
AMapController::AMapController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mapType = EMapType::MT_Normal;
	mapLoopType = EMapLoopType::MLT_Loop;
	speedBuff = 1.f;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);

	startBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	if (startBoxComponent) {
		startBoxComponent->SetWorldLocation(FVector(-3533.5, 1420., 319.));
		startBoxComponent->SetWorldScale3D(FVector(2., 15.5, 10.));
		startBoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
		startBoxComponent->SetupAttachment(mesh);
	}
	startBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMapController::OnOverlapBeginPlayer);
}

// Called when the game starts or when spawned
void AMapController::BeginPlay()
{
	Super::BeginPlay();

}

void AMapController::OnOverlapBeginPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		if (ChangedMapType.IsBound())
			ChangedMapType.Broadcast(this);
	}
}

void AMapController::SetActive(bool isActive)
{
	SetActorHiddenInGame(!isActive);
}

