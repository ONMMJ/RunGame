// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagnetableItem.h"
#include "EatableItem.h"
#include "ExpObject.generated.h"

class UNiagaraComponent;

UCLASS()
class RUNGAME_API AExpObject : public AMagnetableItem, public IEatableItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExpObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* boxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float exp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* NS_idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* NS_eat;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// IEatableItem��(��) ���� ��ӵ�
	virtual void ActiveItem_Implementation(AMyPlayer* player) override;

	virtual void SetActive(bool isActive) override;

	UFUNCTION(BlueprintCallable)
	void NS_eatFinished();
};
