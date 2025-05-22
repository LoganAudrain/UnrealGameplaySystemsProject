// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/MenuPlayerController.h"
#include "Blueprint/UserWidget.h"

AMenuPlayerController::AMenuPlayerController()
	: MenuWidget(nullptr)
{
	bShowMouseCursor = true;
}

void AMenuPlayerController::BeginPlay()
{
	MenuWidget = CreateWidget<UUserWidget>(this, MenuClass);
	MenuWidget->AddToViewport();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetWidgetToFocus(MenuWidget->TakeWidget());

	SetInputMode(InputMode);
}
