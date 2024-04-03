// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/StreamableManager.h>
#include "Engine/AssetManager.h"

ULevelManager* ULevelManager::Instance = nullptr;

ULevelManager* ULevelManager::GetInstance()
{
    if (Instance == nullptr)
    {
        Instance = NewObject<ULevelManager>();
    }
    return Instance;
}

void ULevelManager::CleanupInstance()
{
    if (Instance != nullptr) {
        Instance = nullptr;
    }
}

ULevelManager::ULevelManager()
{
}

void ULevelManager::LoadLevel(FName LevelName)
{
    UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0), LevelName);
}