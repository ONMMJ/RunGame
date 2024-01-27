// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	
#include "GameFramework/Actor.h"
#include "RoadCollider.generated.h"

UENUM(BlueprintType)
enum class ETurnDirection : uint8
{
	TD_None UMETA(DisplayName = "None"),
	TD_Left UMETA(DisplayName = "Left"),
	TD_Right UMETA(DisplayName = "Right"),
};

UCLASS()
class RUNGAME_API ARoadCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoadCollider();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* boxComponent;
	
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Coner")
	ETurnDirection turnDirection;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Coner")
	float turnPer;
};
