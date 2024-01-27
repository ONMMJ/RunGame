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

	//현제 이용중인 플레이어 컨트롤러를 얻어옴.
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// 전체 버튼 패널
	optionButtonListPanel = Cast<UWidget>(GetWidgetFromName(TEXT("ButtonPanel")));
	optionButtonListPanel->SetVisibility(ESlateVisibility::Collapsed);

	// 버튼 패널
	optionButtonPanel.Add(Cast<UWidget>(GetWidgetFromName(TEXT("SizeBox_1"))));
	optionButtonPanel.Add(Cast<UWidget>(GetWidgetFromName(TEXT("SizeBox_2"))));
	optionButtonPanel.Add(Cast<UWidget>(GetWidgetFromName(TEXT("SizeBox_3"))));
	optionButtonPanel.Add(Cast<UWidget>(GetWidgetFromName(TEXT("SizeBox_4"))));

	// 버튼
	optionButtonList.Add(Cast<UButton>(GetWidgetFromName(TEXT("OptionButton_1"))));
	optionButtonList.Add(Cast<UButton>(GetWidgetFromName(TEXT("OptionButton_2"))));
	optionButtonList.Add(Cast<UButton>(GetWidgetFromName(TEXT("OptionButton_3"))));
	optionButtonList.Add(Cast<UButton>(GetWidgetFromName(TEXT("OptionButton_4"))));

	// 버튼 타이틀
	optionTitleList.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("OptionTitle_1"))));
	optionTitleList.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("OptionTitle_2"))));
	optionTitleList.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("OptionTitle_3"))));
	optionTitleList.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("OptionTitle_4"))));

	// 버튼 이미지
	optionImageList.Add(Cast<UImage>(GetWidgetFromName(TEXT("OptionImage_1"))));
	optionImageList.Add(Cast<UImage>(GetWidgetFromName(TEXT("OptionImage_2"))));
	optionImageList.Add(Cast<UImage>(GetWidgetFromName(TEXT("OptionImage_3"))));
	optionImageList.Add(Cast<UImage>(GetWidgetFromName(TEXT("OptionImage_4"))));

	// 버튼 설명
	optionTextList.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("OptionText_1"))));
	optionTextList.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("OptionText_2"))));
	optionTextList.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("OptionText_3"))));
	optionTextList.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("OptionText_4"))));	
}

void UWidget_OptionButton::SetOption(TArray<FOptionInfo> optionList)
{
	if (optionButtonPanel.Num() != optionList.Num())
	{
		for (int i = 0; i < optionButtonPanel.Num(); i++)
		{
			if (i < optionList.Num())
				optionButtonPanel[i]->SetVisibility(ESlateVisibility::Visible);
			else
				optionButtonPanel[i]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UWidget_OptionButton::SetButtonUI(FOptionInfo optionInfo, int index)
{
	optionTitleList[index]->SetText(FText::FromString(optionInfo.title));
	optionImageList[index]->SetBrushFromTexture(optionInfo.image);
	optionTextList[index]->SetText(FText::FromString(optionInfo.optionText));
}

//===================================================================================
#pragma region BuffOptionList

void UWidget_OptionButton::SetOptionUI()
{
	StopGame();

	int panelCount = optionButtonPanel.Num();
	TArray<FOptionInfo> optionList = buffOptionData->RandomPickupOption(player->buffOptionCount);
	if (panelCount != optionList.Num())
	{
		for (int i = 0; i < panelCount; i++)
		{
			if (i < optionList.Num())
			{
				optionButtonPanel[i]->SetVisibility(ESlateVisibility::Visible);
				SelectOption(optionButtonList[i], optionList[i].id);
				SetButtonUI(optionList[i], i);
			}
			else
			{
				optionButtonPanel[i]->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

void UWidget_OptionButton::SelectOption(UButton* button, FString id)
{

	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(id));
	button->OnClicked.Clear();
	if (id.Contains(TEXT("MaxHpUp")))
		button->OnClicked.AddDynamic(this, &UWidget_OptionButton::Option_MaxHpUp);
	else if (id.Contains(TEXT("HpDownSlowly")))
		button->OnClicked.AddDynamic(this, &UWidget_OptionButton::Option_HpDownSlowly);
	else if (id.Contains(TEXT("SpeedUp")))
		button->OnClicked.AddDynamic(this, &UWidget_OptionButton::Option_SpeedUp);
	else if (id.Contains(TEXT("GrowUp")))
		button->OnClicked.AddDynamic(this, &UWidget_OptionButton::Option_GrowUp);
	else if (id.Contains(TEXT("AddShield")))
		button->OnClicked.AddDynamic(this, &UWidget_OptionButton::Option_AddShield);


	button->OnClicked.AddDynamic(this, &UWidget_OptionButton::StartGame);
}


void UWidget_OptionButton::StartGame()
{
	optionButtonListPanel->SetVisibility(ESlateVisibility::Collapsed);
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	if (!ensure(PlayerController != nullptr)) return;
	//마우스커서 안 보이게하기
	PlayerController->bShowMouseCursor = false;
}

void UWidget_OptionButton::StopGame()
{
	optionButtonListPanel->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	if (!ensure(PlayerController != nullptr)) return;

	//마우스커서 보이게하기
	PlayerController->bShowMouseCursor = true;
}

void UWidget_OptionButton::Option_MaxHpUp()
{
	UE_LOG(LogTemp, Warning, TEXT("MaxHpUp"));
}

void UWidget_OptionButton::Option_HpDownSlowly()
{
	UE_LOG(LogTemp, Warning, TEXT("HpDownSlowly"));
}

void UWidget_OptionButton::Option_SpeedUp()
{ 
	mapManager->AddSpeed(1.f);
	player->AddSpeed(20.f);
}

void UWidget_OptionButton::Option_GrowUp()
{
	UE_LOG(LogTemp, Warning, TEXT("GrowUp"));
}

void UWidget_OptionButton::Option_AddShield()
{
	UE_LOG(LogTemp, Warning, TEXT("AddShield"));
}

#pragma endregion

