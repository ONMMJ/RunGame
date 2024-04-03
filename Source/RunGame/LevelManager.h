// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelManager.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API ULevelManager : public UObject
{
	GENERATED_BODY()

public:
    // Singleton instance accessor
    UFUNCTION(BlueprintCallable)
    static ULevelManager* GetInstance();

    static void CleanupInstance();

    // Function to load a new level
    UFUNCTION(BlueprintCallable)
    void LoadLevel(FName LevelName);

private:
    // Private constructor
    ULevelManager();

    // Singleton instance
    static ULevelManager* Instance;
};
