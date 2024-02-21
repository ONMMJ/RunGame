// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_OptionButton.h"
#include "MyPlayer.h"
#include "MapManager.h"
#include "BuffOptionData.h"
#include "Components/Widget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UWidget_OptionButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Get MapManager
	TArray<AActor*> arrOutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMapManager::StaticClass(), arrOutActors);
	if (IsValid(arrOutActors[0]))
		mapManager = Cast<AMapManager>(arrOutActors[0]);

	//���� �̿����� �÷��̾� ��Ʈ�ѷ��� ����.
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// ��ü ��ư �г�
	optionButtonListPanel = Cast<UWidget>(GetWidgetFromName(TEXT("ButtonPanel")));
	optionButtonListPanel->SetVisibility(ESlateVisibility::Collapsed);
}


//===================================================================================
#pragma region BuffOptionList

void UWidget_OptionButton::StartGame()
{
	optionButtonListPanel->SetVisibility(ESlateVisibility::Collapsed);
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	if (!ensure(PlayerController != nullptr)) return;
	//���콺Ŀ�� �� ���̰��ϱ�
	PlayerController->bShowMouseCursor = false;
}

void UWidget_OptionButton::StopGame()
{
	optionButtonListPanel->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	if (!ensure(PlayerController != nullptr)) return;

	//���콺Ŀ�� ���̰��ϱ�
	PlayerController->bShowMouseCursor = true;
}

void UWidget_OptionButton::Option_MaxHpUp(float value)
{
	player->AddMaxHp(value);
}

void UWidget_OptionButton::Option_HpDownSlowly(float value)
{
	player->SubHpDownBuff(value);
}

void UWidget_OptionButton::Option_SpeedUp(float value)
{ 
	mapManager->AddSpeed(value);
}

void UWidget_OptionButton::Option_GrowUp(float value)
{
	player->AddBonusExp(value);
}

void UWidget_OptionButton::Option_AddShield(float value)
{
	UE_LOG(LogTemp, Warning, TEXT("AddShield"));
}

#pragma endregion

