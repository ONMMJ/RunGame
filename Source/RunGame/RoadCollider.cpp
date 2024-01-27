// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadCollider.h"
#include "TrafficLight.h"
#include <Components/BoxComponent.h>

// Sets default values
ARoadCollider::ARoadCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	if (boxComponent) {
		RootComponent = boxComponent;
		boxComponent->SetCollisionProfileName(TEXT("RoadCollision"));
	}

}