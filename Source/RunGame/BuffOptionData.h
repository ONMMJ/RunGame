// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BuffOptionData.generated.h"

USTRUCT(BlueprintType)
struct FOptionInfo {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* image;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString optionText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 persentCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float value;
};

UCLASS()
class RUNGAME_API UBuffOptionData : public UDataAsset
{
	GENERATED_BODY()

    public:
        UPROPERTY(EditAnywhere)
        TArray<FOptionInfo> optionList;

    public:
        UFUNCTION(BlueprintCallable)
        TArray<FOptionInfo> RandomPickupOption(int num);
    private:
        int SumPersentCount();
};
