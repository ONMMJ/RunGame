// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttack.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AEnemyAttack::AEnemyAttack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	damageArea = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DamageArea"));
	RootComponent = damageArea;
	damageArea->SetCollisionProfileName(TEXT("Enemy"));
	damageArea->SetGenerateOverlapEvents(true);

	// info
	beforeDelayTime = 3.f;
	afterDelayTime = 1.f;
	damage = 10.f;
}

void AEnemyAttack::BeginPlay()
{
	Super::BeginPlay();
}