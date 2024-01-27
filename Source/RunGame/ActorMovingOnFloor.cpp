// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorMovingOnFloor.h"
#include "MapController.h"

// Sets default values
AActorMovingOnFloor::AActorMovingOnFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorMovingOnFloor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<FHitResult> hits;
	FVector start = GetActorLocation();
	FVector direction = GetActorUpVector() * -1;
	FVector end = start + direction * 100.f;

	bool gotHits = GetWorld()->LineTraceMultiByChannel(hits, start, end, ECC_Visibility);
	if (gotHits)
	{
		for (int i = 0; i < hits.Num(); i++)
		{
			FHitResult hit = hits[i];
			if (hit.GetActor())
			{
				AMapController* map = Cast<AMapController>(hit.GetActor());
				if (IsValid(map))
				{
					AttachToActor(map, FAttachmentTransformRules::KeepWorldTransform);
					break;
				}
			}
		}
	}
}

// Called every frame
void AActorMovingOnFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

