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

	SetOptionList();
	levelUpPoint = 0;

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

void UWidget_OptionButton::SetOptionList()
{
	// DataAsset�� Option������ TMap(optionList)�� ����
	optionArray = buffOptionData->GetOptionList();
	for (int i = 0; i < optionArray.Num(); i++)
	{
		FOptionInfo* optionInfo = &optionArray[i];
		optionList.Add(optionArray[i].id, optionInfo);
	}
}


TArray<FString> UWidget_OptionButton::RandomPickupOption(int num)
{
	int maxPerCount = SumPersentCount();
	TArray<FOptionInfo> tempList = GetRemainOption();
	TArray<FString> result;
	for (int i = 0; i < num; i++)
	{
		int sumPerCount = 0;
		int perCount = FMath::RandRange(1, maxPerCount);
		UE_LOG(LogTemp, Warning, TEXT("%d, %d, %d"), optionList.Num(), tempList.Num(), SumPersentCount());
		if (tempList.Num() > 0) {
			for (int j = 0; j<tempList.Num();j++)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s ,%d, %d"), *tempList[j].id, perCount, maxPerCount);
				if (tempList[j].level < tempList[j].maxLevel)
					sumPerCount += tempList[j].persentCount;
				else
				{
					continue;
				}
				// Ȯ��ī��Ʈ ���� ������ �����̸�
				if (perCount <= sumPerCount)
				{
					result.Add(tempList[j].id);
					maxPerCount -= tempList[j].persentCount;
					tempList.RemoveAt(j);
					break;
				}
			}
		}
		else
		{
			result.Add(TEXT("None"));
		}
	}
	int index = FMath::RandRange(0, 4);
	return result;
}

void UWidget_OptionButton::AddOptionLevel(FString optionId)
{
	optionList[optionId]->level++;
}
FOptionInfo UWidget_OptionButton::GetOptionInfo(FString optionId)
{
	return *optionList[optionId];
}
int UWidget_OptionButton::SumPersentCount()
{
	int sum = 0;
	int a = optionList[TEXT("MaxHpUp")]->level;
	UE_LOG(LogTemp, Warning, TEXT("%d"), optionArray[0].level);
	UE_LOG(LogTemp, Warning, TEXT("%d"), a);
	for (auto var : optionList)
	{
		UE_LOG(LogTemp, Warning, TEXT("dddddd"));
		UE_LOG(LogTemp, Warning, TEXT("%d, %d"), var.Value->level, var.Value->maxLevel);
		if (var.Value->level < var.Value->maxLevel)
			sum += var.Value->persentCount;
	}
	return sum;
}
TArray<FOptionInfo> UWidget_OptionButton::GetRemainOption()
{
	TMap<FString, FOptionInfo*> tempList = optionList;
	TArray<FOptionInfo> result;
	for (auto var : tempList)
	{
		if (var.Value->level < var.Value->maxLevel)
			result.Add(*var.Value);
	}
	return result;
}
//===================================================================================
#pragma region BuffOptionList

void UWidget_OptionButton::PlayerLevelUp()
{
	levelUpPoint++;
	if (levelUpPoint > 1)
		return;
	SetOptionUI(player->buffOptionCount);
}
void UWidget_OptionButton::InvokeOptionFunc(FString optionId)
{
	//optionFuncMap[optionId](this);
}
void UWidget_OptionButton::StartGame()
{
	optionButtonListPanel->SetVisibility(ESlateVisibility::Collapsed);
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	levelUpPoint--;
	if (levelUpPoint > 0)
	{
		SetOptionUI(player->buffOptionCount);
	}

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

//void UWidget_OptionButton::SetOptionFuncMap()
//{
//	// Option�� ������ �Լ��� TMap�� ����
//	optionFuncMap.Add(TEXT("MaxHpUp"), &UWidget_OptionButton::Option_MaxHpUp)
//}

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

