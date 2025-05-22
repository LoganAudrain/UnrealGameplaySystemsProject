// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/GamePlayerController.h"

void AGamePlayerController::BeginPlay()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
