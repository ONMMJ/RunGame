// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "LevelManager.h"

void UMyGameInstance::Shutdown()
{
    Super::Shutdown(); // Call parent class's Shutdown function

    // Clean up ULevelManager instance
    ULevelManager::CleanupInstance();
}
