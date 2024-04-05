// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "Components/SphereComponent.h"
#include "Widget_OptionButton.h"
#include "EatableItem.h"
#include "MagnetableInterface.h"
#include <Kismet/GameplayStatics.h>

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// Sets default values
AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnOverlapBegin);

	// Don't rotate when the controller rotates. Let that just affect the camer
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// CharaterMovement
	//GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	JumpMaxCount = 2;

	magnetCollision = CreateDefaultSubobject<USphereComponent>(TEXT("MagnetCollision"));
	magnetCollision->SetCollisionProfileName(TEXT("Magnet"));
	magnetCollision->SetupAttachment(GetCapsuleComponent());
	magnetCollision->SetGenerateOverlapEvents(true);

	// 위아래로 이동하지 않을 때 정면을 바라보는 시간
	rotationTime = 0.5f;

	// Status
	Init();
}

void AMyPlayer::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	GameStart();
	magnetCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnOverlapBeginMagnet);


	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	yawRotation = FRotator(0, Rotation.Yaw, 0);

	//Add OptionButtonList Widget
	if (IsValid(optionButtonWidgetClass))
	{
		optionButtonWidget = Cast<UWidget_OptionButton>(CreateWidget(GetWorld(), optionButtonWidgetClass));
		if (IsValid(optionButtonWidget))
		{
			optionButtonWidget->AddToViewport();
		}
	}

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	GetCharacterMovement()->MaxWalkSpeed = speed;
}
// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// find out which way is forward
	//const FRotator Rotation = Controller->GetControlRotation();
	//const FRotator YawRotation(0, Rotation.Yaw, 0);
	//const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//AddMovementInput(ForwardDirection, 1);	// 1: 전진, -1: 후진

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		if (currentRotationTime <= rotationTime)
		{
			// 초기화
			if (currentRotationTime == 0.f)
			{
				double yAcceleration = GetCharacterMovement()->GetCurrentAcceleration().Y;
				if (yAcceleration > 0.)
				{
					isMoveFront = false;
					moveNegative = 1;
				}
				else if (yAcceleration == 0.)
					isMoveFront = true;
				else
				{
					isMoveFront = false;
					moveNegative = -1;
				}
			}

			//UE_LOG(LogTemplateCharacter, Error, TEXT("%f, cur: %f, flag: %s"), GetCharacterMovement()->GetCurrentAcceleration().Y, currentRotationTime, isMoveFront ? TEXT("true") : TEXT("false"));
			// 현재 회전 시간을 더해준다.
			currentRotationTime += DeltaTime;
			//UE_LOG(LogTemp, Error, TEXT("%f"), currentRotationTime);
			// 현재 lerp에 들어갈 알파 값 = 현재 시간 / 회전에 걸리는 시간
			float t = currentRotationTime / rotationTime;
			FRotator angle = GetActorRotation();
			FRotator YMoveDirection = FRotator::ZeroRotator;

			if (!isMoveFront)
			{
				float turnAngle;
				if (speed > 599.f)
					turnAngle = 30.f;
				else if (speed > 100.f)
					turnAngle = speed / 600.f * 30.f;
				else
					turnAngle = 5.f;

				YMoveDirection.Yaw = YMoveDirection.Yaw + (turnAngle * moveNegative);
			}

			// 월드기준 앞방향으로 t초에 걸쳐 회전
			angle = FMath::Lerp<FRotator>(angle, YMoveDirection, t);
			SetActorRotation(angle);
		}
	}

	if (hp > 0) {
		hp -= hpDownPerSecond * hpDownBuff * DeltaTime;
	}
	else
	{
		GameOver();
	}
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);
		EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Started, this, &AMyPlayer::StartMove);
		EnhancedInputComponent->BindAction(MoveDownAction, ETriggerEvent::Started, this, &AMyPlayer::StartMove);
		EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Completed, this, &AMyPlayer::EndMove);
		EnhancedInputComponent->BindAction(MoveDownAction, ETriggerEvent::Completed, this, &AMyPlayer::EndMove);
	}
	else {
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component!This template is built to use the Enhanced Input system.If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMyPlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(UEatableItem::StaticClass()))
	{
		IEatableItem::Execute_ActiveItem(OtherActor, this);
	}
}

void AMyPlayer::OnOverlapBeginMagnet(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!isMagnet)
		return;
	if (OtherActor->GetClass()->ImplementsInterface(UMagnetableInterface::StaticClass()))
	{
		IMagnetableInterface::Execute_Targetting(OtherActor, this);
	}
}

void AMyPlayer::StartMove(const FInputActionValue& Value)
{
	currentRotationTime = 0.f;
}

void AMyPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D inputVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		//AddMovementInput(ForwardDirection, inputVector.X);
		AddMovementInput(RightDirection, inputVector.Y);		
	}
}

void AMyPlayer::EndMove(const FInputActionValue& Value)
{
	currentRotationTime = 0.f;
}

void AMyPlayer::Init() 
{
	// Stat
	magnetLevel = 0;
	firstSpeed = 450.f;
	maxHp = 100.f;
	hpDownPerSecond = 1.f;
	expUpPerSecond = 1.f;
	level = 1;
	bonusExp = 0.f;
	nowExp = 0.f;
	nextExp = 30.f;
	damagedTime = 3.f;

	hpDownBuff = 1.f;
	expUpBuff = 1.f;
	expObjectBuff = 1.f;

	buffOptionCount = 3;
}

void AMyPlayer::GameStart()
{
	// 시작 세팅
	startPos = GetActorLocation();
	direction = 1;	// 1: 전진, -1: 후진
	hp = maxHp;
	speed = firstSpeed;
	isMoveFront = true;
	isMove = true;
	isMagnet = false;

	// 기본 세팅
	magnetLevel = 0;
	hpDownPerSecond = 1.f;
	expUpPerSecond = 1.f;
	level = 1;
	nowExp = 0.f;
	nextExp = 30.f;

	hpDownBuff = 1.f;
	expUpBuff = 1.f;
	expObjectBuff = 1.f;

	//buffOptionCount = 3;
}

void AMyPlayer::SetSpeed(float mapSpeed)
{
	speed = mapSpeed * 30.f;
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void AMyPlayer::GetExp(float exp)
{
	nowExp += exp;
	nowExp += bonusExp;
	while (nowExp >= nextExp) {
		nowExp -= nextExp;
		LevelUp();
		nextExp = GetNextExp();
	}
}

void AMyPlayer::LevelUp()
{
	level++;
	isMoveFront = true;
	optionButtonWidget->PlayerLevelUp();
}

void AMyPlayer::GameOver_Implementation()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!ensure(PlayerController != nullptr)) return;

	//마우스커서 보이게하기
	PlayerController->bShowMouseCursor = true;
}



float AMyPlayer::GetNextExp()
{
	return 30.f + ((level - 1) * 10.f);
}

void AMyPlayer::AddBonusExp(float value)
{
	bonusExp += value;
}


void AMyPlayer::SubHpDownBuff(float value)
{
	float result = value / 100.f;
	hpDownBuff -= result;
}

void AMyPlayer::AddMaxHp(float value)
{
	maxHp += value;
	hp += value;
}

void AMyPlayer::SetMagnet(float value)
{
	if (magnetLevel > 0)
	{
		float mulScaleValue = 1.1f;
		FVector scale = magnetCollision->GetRelativeScale3D() * mulScaleValue;
		magnetCollision->SetRelativeScale3D(scale);
	}
	else 
	{
		isMagnet = true;
	}
	magnetLevel += value;
	UE_LOG(LogTemp, Warning, TEXT("magnetLevel: %d, addValue: %f"), magnetLevel, value);
}

void AMyPlayer::GetDamaged_Implementation(float damage)
{
	if (isDamaged)
		return;
	hp -= damage;
	FTimerHandle timeHandle;

	isDamaged = true;
	GetWorldTimerManager().SetTimer(timeHandle, this, &AMyPlayer::DamagedNext, damagedTime, false);

	//OnNoticePlayerDamagedStart();


	//mapManager->SetPlayerDamaged(true);
	//GetCharacterMovement()->MaxWalkSpeed = speed * mapManager->playerDamagedSpeed;
}

void AMyPlayer::DamagedNext_Implementation()
{
	isDamaged = false;

	//OnNoticePlayerDamagedEnd();
	//GetCharacterMovement()->MaxWalkSpeed = speed;
	//mapManager->SetPlayerDamaged(false);

}
