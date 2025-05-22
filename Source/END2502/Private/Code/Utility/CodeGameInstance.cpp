// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Utility/CodeGameInstance.h"
#include "../END2502.h"


UCodeGameInstance::UCodeGameInstance()
{
	FirstLevelIndex = 1;

	GameLevels = {
		FName("CodeMainMenu"),
		FName("CodeTestingMap"),
	};
}

void UCodeGameInstance::LoadLevelSafe(const int& levelIndex)
{
	/*
		See UGameplayStatics::OpenLevel to use a reference
	*/

	if (levelIndex < 0 || levelIndex >= GameLevels.Num())
	{
		UE_LOG(Game, Error, TEXT("UCodeGameInstance::LoadLevelSafe -> Level index %d is not valid"), levelIndex);
		return;
	}

	UWorld* world = GetWorld();
	if (!world)
	{
		UE_LOG(Game, Error, TEXT("UCodeGameInstance::LoadLevelSafe -> Failed to get World context"));
		return;
	}

	FName levelName = GameLevels[levelIndex];
	FString cmd = levelName.ToString();
	FString levelNameStr = levelName.ToString();

	if (!GEngine->MakeSureMapNameIsValid(levelNameStr))
	{
		UE_LOG(Game, Warning, TEXT("UCodeGameInstance::LoadLevelSafe -> WARNING: The map '%s' does not exist."), *cmd);
		return;
	}

	APlayerController* controller = world->GetFirstPlayerController();
	controller->ClientTravel(cmd, TRAVEL_Absolute);
	UE_LOG(Game, Log, TEXT("UCodeGameInstance::LoadLevelSafe -> Travelling to level: %s"), *cmd);
}

void UCodeGameInstance::LoadFirstLevel()
{
	LoadLevelSafe(FirstLevelIndex);
}

void UCodeGameInstance::QuitTheGame()
{
	UWorld* world = GetWorld();
	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("UCodeGameInstance::QuitTheGame -> World ptr is null"));
		return;
	}

	APlayerController* playerController = world->GetFirstPlayerController();
	if (!playerController)
	{
		UE_LOG(LogTemp, Error, TEXT("UCodeGameInstance::QuitTheGame -> PlayerController ptr is null"));
		return;
	}

	playerController->ConsoleCommand("quit");
}
