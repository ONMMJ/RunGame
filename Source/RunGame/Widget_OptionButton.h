// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_OptionButton.generated.h"

struct FOptionInfo;
class UTextBlock;
class UButton;
class UWidget;
class UImage;

UCLASS()
class RUNGAME_API UWidget_OptionButton : public UUserWidget
{
		GENERATED_BODY()

		UPROPERTY()
		APlayerController* PlayerController;

		//UPROPERTY()
		//TMap<FString, TFunction<void(UWidget_OptionButton*)>> optionFuncMap;
	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AMyPlayer* player;

		// MapManager
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class AMapManager* mapManager;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset")
		class UBuffOptionData* buffOptionData;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataAsset")
		TArray<FOptionInfo> optionArray;

		TMap<FString, FOptionInfo*> optionList;


		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UWidget* optionButtonListPanel;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int levelUpPoint;
	protected:
		virtual void NativeOnInitialized();

		/** Buff Option Func **/

		UFUNCTION(BlueprintCallable)
		void StartGame();
		UFUNCTION(BlueprintCallable)
		void StopGame();
		UFUNCTION(BlueprintCallable)
		void Option_MaxHpUp(float value);
		UFUNCTION(BlueprintCallable)
		void Option_HpDownSlowly(float value);
		UFUNCTION(BlueprintCallable)
		void Option_SpeedUp(float value);
		UFUNCTION(BlueprintCallable)
		void Option_GrowUp(float value);
		UFUNCTION(BlueprintCallable)
		void Option_AddShield(float value);
	private:

		void SetOptionList();
		//void SetOptionFuncMap();
		int SumPersentCount();
		TArray<FOptionInfo> GetRemainOption();
	public:
		void PlayerLevelUp();
		UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetOptionUI(int optionCount);

		UFUNCTION(BlueprintCallable)
		TArray<FString> RandomPickupOption(int num);
		UFUNCTION(BlueprintCallable)
		void AddOptionLevel(FString optionId);
		UFUNCTION(BlueprintCallable)
		FOptionInfo GetOptionInfo(FString optionId);

		UFUNCTION(BlueprintCallable)
		void InvokeOptionFunc(FString optionId);
};
