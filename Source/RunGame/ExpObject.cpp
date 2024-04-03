// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpObject.h"
#include "MyPlayer.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"

// Sets default values
AExpObject::AExpObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = boxCollider;
	boxCollider->SetCollisionProfileName(TEXT("Exp"));
	boxCollider->SetGenerateOverlapEvents(true);

	// ù ��° Niagara ������Ʈ ���� �� ����
	NS_idle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraIdle"));
	NS_idle->SetupAttachment(RootComponent); // ����
	// NiagaraComponent1�� ���� �߰� ���� ����

	// �� ��° Niagara ������Ʈ ���� �� ����
	NS_eat = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEat"));
	NS_eat->SetupAttachment(RootComponent); // ����
}
void AExpObject::BeginPlay()
{
	Super::BeginPlay();
	isTargetting = false;
	//NS_eat->OnSystemFinished.AddDynamic(this, NS_eatFinished);
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
		boxCollider->SetGenerateOverlapEvents(false);
		SetActive(false);
	}
}

void AExpObject::SetActive(bool isActive)
{
	if (isActive)
	{
		SetActorHiddenInGame(false);
		boxCollider->SetGenerateOverlapEvents(true);
		DetachFloor();
		AttachFloor();
		NS_idle->Activate();
		NS_eat->DeactivateImmediate();
	}
	else
	{
		NS_idle->DeactivateImmediate();
		NS_eat->Activate();
	}
}

void AExpObject::NS_eatFinished()
{
	SetActorHiddenInGame(true);
}




