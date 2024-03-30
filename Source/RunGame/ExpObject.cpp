// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpObject.h"
#include "MyPlayer.h"
#include <Components/SphereComponent.h>

// Sets default values
AExpObject::AExpObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));
	RootComponent = staticMesh;
	staticMesh->SetCollisionProfileName(TEXT("Exp"));
	staticMesh->SetGenerateOverlapEvents(true);
}
void AExpObject::BeginPlay()
{
	Super::BeginPlay();
	isTargetting = false;
}

void AExpObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void AExpObject::ActiveItem_Implementation(AMyPlayer* player)
{
	if (IsValid(player))
	{
		player->GetExp(exp);
		isTargetting = false;
		SetActive(false);
	}
}


