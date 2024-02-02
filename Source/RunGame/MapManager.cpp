// Fill out your copyright notice in the Description page of Project Settings.


#include "MapManager.h"
#include "MapController.h"

// Sets default values
AMapManager::AMapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	direction = FVector::BackwardVector;
	speed = 10.f; 
	playerDamagedSpeed = 0.5f;
	mapSpeedBuff = 1.f;
	speedBuff = 1.f;
	totalSpeed = 0.f;
	nextMapTypeTime = 30.f;
}

// Called when the game starts or when spawned
void AMapManager::BeginPlay()
{
	Super::BeginPlay();

	nextMapType = EMapType::MT_Normal;
	nextMapLoopType = EMapLoopType::MLT_Loop;

	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, this, &AMapManager::SetNextMapType, nextMapTypeTime, true);

	if (allMapList.Num() > 0)
	{
		UWorld* world = GetWorld();
		FRotator rotator = FRotator::ZeroRotator;
		FVector spawnLocation = FVector::ZeroVector;
		for (auto temp : allMapList)
		{
			if (!IsValid(temp))
				continue;
			AMapController* map = world->SpawnActor<AMapController>(temp, spawnLocation, rotator);
			if (IsValid(map))
			{
				AddSwitchMapType(map);
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (!IsValid(moveActorList[i].parent))
			return;
		AMapController* map = GetMap(nextMapType, nextMapLoopType);
		if (IsValid(map))
		{
			moveActorList[i].child = map;
			map->AttachToActor(moveActorList[i].parent, FAttachmentTransformRules::KeepRelativeTransform);
			map->SetActorRelativeLocation(FVector::ZeroVector);
			map->SetActive(true);
		}

	}
}

// Called every frame
void AMapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < 3; i++) 
	{
		if (!IsValid(moveActorList[i].parent))
			return;

		FVector location = moveActorList[i].parent->GetActorLocation();
		if (location.X <= -14400.)
		{
			int nextActorIndex = (i + 2) % 3;
			location = moveActorList[nextActorIndex].parent->GetActorLocation();
			location.X += 7200.;
			moveActorList[i].parent->SetActorLocation(location);
			AddSwitchMapType(moveActorList[i].child);

			AMapController* map = GetMap(nextMapType, nextMapLoopType);
			if (IsValid(map))
			{
				moveActorList[i].child = map;
				map->AttachToActor(moveActorList[i].parent, FAttachmentTransformRules::KeepRelativeTransform);
				map->SetActorRelativeLocation(FVector::ZeroVector);
				map->SetActive(true);
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (!IsValid(moveActorList[i].parent))
			return;

		FVector location = moveActorList[i].parent->GetActorLocation();
		totalSpeed = speed * mapSpeedBuff * speedBuff * (isPlayerDamaged ? playerDamagedSpeed : 1.f);
		location += direction * totalSpeed;

		moveActorList[i].parent->SetActorLocation(location);
	}
}

void AMapManager::AddSwitchMapType(AMapController* map)
{
	if (IsValid(waitingMapParentActor))
	{
		map->AttachToActor(waitingMapParentActor, FAttachmentTransformRules::KeepRelativeTransform);
	}

	FMapWaitingList* temp;
	switch (map->mapType)
	{
	case EMapType::MT_Normal:
		temp = &normalMapList;
		break;
	case EMapType::MT_Snow:
		temp = &snowMapList;
		break;
	default:
		temp = nullptr;
		break;
	}

	if (temp)
	{
		switch (map->mapLoopType)
		{
		case EMapLoopType::MLT_Start:
			temp->start.Add(map);
			break;
		case EMapLoopType::MLT_Loop:
			temp->loop.Add(map);
			break;
		default:
			break;
		}
	}
	map->SetActive(false);
}

void AMapManager::SetSpeed(float inputSpeed)
{
	speed = inputSpeed;
}

void AMapManager::AddSpeed(float add)
{
	speed += add;
}

void AMapManager::AddSpeedBuff(float buff)
{
	speedBuff *= buff;
}

void AMapManager::RemoveSpeedBuff(float buff)
{
	speedBuff /= buff;
}

void AMapManager::SetPlayerDamaged(bool isDamaged)
{
	isPlayerDamaged = isDamaged;
}

void AMapManager::SetNextMapType()
{
	nextMapType = EMapType(((int)nextMapType + 1) % (int)EMapType::MT_Num);
	//nextMapLoopType = EMapLoopType::MLT_Start;
}

AMapController* AMapManager::GetMap(EMapType mapType, EMapLoopType mapLoopType)
{
	FMapWaitingList* temp;
	AMapController* result = nullptr;
	switch (mapType)
	{
	case EMapType::MT_Normal:
		temp = &normalMapList;
		break;
	case EMapType::MT_Snow:
		temp = &snowMapList;
		break;
	default:
		temp = nullptr;
		break;
	}

	TArray<AMapController*>* temp2 = nullptr;
	if (temp)
	{
		switch (mapLoopType)
		{
		case EMapLoopType::MLT_Start:
			temp2 = &temp->start;
			nextMapLoopType = EMapLoopType::MLT_Loop;
			break;
		case EMapLoopType::MLT_Loop:
			temp2 = &temp->loop;
			break;
		default:
			break;
		}
	}

	if (temp2)
	{
		if (temp2->Num() > 0)
		{
			int index = FMath::RandRange(0, temp2->Num() - 1);
			UE_LOG(LogTemp, Warning, TEXT("mapListNum: %d, index: %d"), temp2->Num(), index);
			result = temp2->GetData()[index];
			temp2->RemoveAt(index);
		}
	}

	/*if (temp2.Num() > 0)
	{
		int index = FMath::RandRange(0, temp2.Num()-1);
		UE_LOG(LogTemp, Warning, TEXT("mapListNum: %d, index: %d"), temp2.Num(), index);
		result = temp2[index];
		temp2.RemoveAt(index);
	}
	else
	{
		result = nullptr;
	}*/

	/*if (temp->loop.Num() > 0)
	{
		int index = FMath::RandRange(0, temp->loop.Num()-1);
		UE_LOG(LogTemp, Warning, TEXT("mapListNum: %d, index: %d"), temp->loop.Num(), index);
		result = temp->loop[index];
		temp->loop.RemoveAt(index);
	}
	else
	{
		result = nullptr;
	}*/

	return result;
}
