// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpObject.h"
#include <Components/SphereComponent.h>

// Sets default values
AExpObject::AExpObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));
	RootComponent = staticMesh;
	staticMesh->SetCollisionProfileName(TEXT("Exp"));
	staticMesh->SetGenerateOverlapEvents(true);
}
void AExpObject::BeginPlay()
{
	Super::BeginPlay();
}
void AExpObject::SetActive(bool isActive)
{
	SetActorHiddenInGame(!isActive);
}


