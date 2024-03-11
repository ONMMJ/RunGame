// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorMovingOnFloor.h"
#include "Car.generated.h"


UCLASS()
class RUNGAME_API ACar : public AActorMovingOnFloor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnyWhere)
	bool isStop;

	UPROPERTY(VisibleAnyWhere)
	class ATrafficLight* trafficLight;
public:
	// Sets default values for this actor's properties
	ACar();

	UPROPERTY(VisibleAnyWhere)
	bool isFrontCar;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	class USkeletalMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "MeshList")
	TArray<USkeletalMesh*> meshList;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	class UBoxComponent* frontCarCollision;

	UPROPERTY(EditAnywhere, Category = Move)
	float moveSpeed;

	UPROPERTY(EditAnywhere, Category = Move)
	float destroyTime;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float damage;
	//FTransform* frontLeftTire;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBeginRoadCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapBeginFrontCar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEndFrontCar(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CheckTrafficLight();
	void CarDestroy();
};
