// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagnetableItem.h"
#include "EatableItem.h"
#include "ExpObject.generated.h"

UCLASS()
class RUNGAME_API AExpObject : public AMagnetableItem, public IEatableItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExpObject();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* staticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float exp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// IEatableItem을(를) 통해 상속됨
	virtual void ActiveItem_Implementation(AMyPlayer* player) override;
};
