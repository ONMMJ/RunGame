// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class RUNGAME_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> optionButtonWidgetClass;
	UPROPERTY()
	class UWidget_OptionButton* optionButtonWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveUpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveDownAction;


	UPROPERTY()
	int magnetLevel;

	// Turn Info
	UPROPERTY()
	FRotator yawRotation;
	UPROPERTY()
	float currentRotationTime;
	UPROPERTY()
	float rotationTime;
	UPROPERTY()
	bool isMoveFront;
	UPROPERTY()
	double moveNegative;
	UPROPERTY()
	float bonusExp;
	UPROPERTY()
	bool isMagnet;

public:
	// Sets default values for this character's properties
	AMyPlayer();

	// MapManager
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AMapManager* mapManager;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	class USphereComponent* magnetCollision;

	UPROPERTY(BluePrintReadOnly)
	double direction;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	FVector startPos;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	bool isMove;
	// Damaged
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	bool isDamaged;


	// Status
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float hp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float maxHp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float hpDownPerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float expUpPerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float firstSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	int level;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float nowExp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float nextExp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float damagedTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float shieldCount;


	// Buff
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	float mapSpeedBuff;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	float hpDownBuff;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	float expUpBuff;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	float expObjectBuff;

	// BuffOption
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BuffOption")
	int buffOptionCount;

protected:
	// To add mapping context
	virtual void BeginPlay();

	/** Called for movement input */
	void StartMove(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void EndMove(const FInputActionValue& Value);
	void Init();
	void GameStart();
	void LevelUp();
	float GetNextExp();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; 
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapBeginMagnet(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GameOver();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetDamaged(float damage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DamagedNext();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetShield();

	UFUNCTION(BlueprintCallable)
	void SetSpeed(float mapSpeed);

	void GetExp(float exp);

	// LevelUp Option
	void AddBonusExp(float value);
	void SubHpDownBuff(float value);
	void AddMaxHp(float value);
	void SetMagnet(float value);
	void AddShieldCount(float value);
};
