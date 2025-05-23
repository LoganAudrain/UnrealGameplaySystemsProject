// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMenuPlayerController();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	TSubclassOf<UUserWidget> MenuClass;

	virtual void BeginPlay() override;

private:
	class UUserWidget* MenuWidget;
};
