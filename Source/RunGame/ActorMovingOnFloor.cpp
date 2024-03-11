// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorMovingOnFloor.h"
#include "MapController.h"

// Sets default values
AActorMovingOnFloor::AActorMovingOnFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AActorMovingOnFloor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<FHitResult> hits;
	FVector start = GetActorLocation();
	FVector direction = GetActorUpVector() * -1;
	FVector end = start + direction * 500.f;

	bool gotHits = GetWorld()->LineTraceMultiByChannel(hits, start, end, ECC_Visibility);
	if (gotHits)
	{
		for (int i = 0; i < hits.Num(); i++)
		{
			FHitResult hit = hits[i];
			if (hit.GetActor())
			{
				UE_LOG(LogTemp, Error, TEXT("%s, %d"), *hit.GetActor()->GetName(), i);
				AMapController* map = Cast<AMapController>(hit.GetActor());
				if (IsValid(map))
				{
					AttachToActor(map, FAttachmentTransformRules::KeepWorldTransform);
					break;
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("no map"));
			}
		}
	}
}


