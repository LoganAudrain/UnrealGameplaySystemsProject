// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CodeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API UCodeGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	TArray<FName> GameLevels;
	int FirstLevelIndex;

public:
	UCodeGameInstance();

	UFUNCTION(BlueprintCallable)
	void LoadFirstLevel();

	UFUNCTION(BlueprintCallable)
	void QuitTheGame();

private:
	void LoadLevelSafe(const int& levelIndex);
};
