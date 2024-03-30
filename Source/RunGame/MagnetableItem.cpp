// Fill out your copyright notice in the Description page of Project Settings.


#include "MagnetableItem.h"

// Sets default values
AMagnetableItem::AMagnetableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMagnetableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagnetableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isTargetting)
		return;

	FVector direction = target->GetActorLocation() - GetActorLocation();
	direction.Normalize();

	FVector location = GetActorLocation() + (direction * moveSpeed * DeltaTime);
	SetActorLocation(location);
}

void AMagnetableItem::Targetting_Implementation(AActor* actor)
{
	target = actor;
	DetachFloor();
	isTargetting = true;
}

