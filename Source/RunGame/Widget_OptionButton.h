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

	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AMyPlayer* player;

		// MapManager
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class AMapManager* mapManager;

		UPROPERTY(EditAnywhere, Category = "DataAsset")
		class UBuffOptionData* buffOptionData;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UWidget* optionButtonListPanel;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UWidget*> optionButtonPanel;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UButton*> optionButtonList;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UTextBlock*> optionTitleList;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UImage*> optionImageList;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UTextBlock*> optionTextList;

	protected:
		virtual void NativeOnInitialized();

		/** Buff Option Func **/
		void SetOption(TArray<FOptionInfo> optionList);
		void SelectOption(UButton* button, FString id);
		UFUNCTION()
		void StartGame();
		UFUNCTION()
		void StopGame();
		UFUNCTION()
		void Option_MaxHpUp();
		UFUNCTION()
		void Option_HpDownSlowly();
		UFUNCTION()
		void Option_SpeedUp();
		UFUNCTION()
		void Option_GrowUp();
		UFUNCTION()
		void Option_AddShield();
	private:

	public:
		UFUNCTION()
		void SetOptionUI();

		UFUNCTION()
		void SetButtonUI(FOptionInfo optionInfo, int index);
};
