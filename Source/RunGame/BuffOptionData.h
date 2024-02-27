// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BuffOptionData.generated.h"

UENUM(BlueprintType)
enum class EOptionGrade : uint8
{
    OG_Normal UMETA(DisplayName = "Normal"),
    OG_Rare UMETA(DisplayName = "Rare"),
    OG_Unique UMETA(DisplayName = "Unique"),
    OG_Lengendary UMETA(DisplayName = "Lengendary")
};

USTRUCT(Atomic, BlueprintType)
struct FOptionInfo {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EOptionGrade Grade;

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
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int32 level;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 maxLevel = 5;
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
        TArray<FOptionInfo> GetOptionList();
        //UFUNCTION(BlueprintCallable)
        //TArray<FOptionInfo> RandomPickupOption(int num);
    private:
        //int SumPersentCount();
};
