// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BuffOptionData.generated.h"

USTRUCT()
struct FOptionInfo {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FString id;

    UPROPERTY(EditAnywhere)
    FString title;

    UPROPERTY(EditAnywhere)
    UTexture2D* image;

    UPROPERTY(EditAnywhere)
    FString optionText;

    UPROPERTY(EditAnywhere)
    int32 persentCount;
};

UCLASS()
class RUNGAME_API UBuffOptionData : public UDataAsset
{
	GENERATED_BODY()

    public:
        UPROPERTY(EditAnywhere)
        TArray<FOptionInfo> optionList;

    public:
        TArray<FOptionInfo> RandomPickupOption(int num);
    private:
        int SumPersentCount();
};
