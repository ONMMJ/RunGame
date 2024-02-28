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

	//현제 이용중인 플레이어 컨트롤러를 얻어옴.
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// 전체 버튼 패널
	optionButtonListPanel = Cast<UWidget>(GetWidgetFromName(TEXT("ButtonPanel")));
	optionButtonListPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UWidget_OptionButton::SetOptionList()
{
	// DataAsset의 Option정보를 TMap(optionList)에 저장
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
				// 확률카운트 합이 랜덤값 이하이면
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

//void UWidget_OptionButton::SetOptionFuncMap()
//{
//	// Option을 실행할 함수를 TMap에 저장
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

