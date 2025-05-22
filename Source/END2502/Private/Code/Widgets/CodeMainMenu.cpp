// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Widgets/CodeMainMenu.h"
#include "Code/Widgets/ButtonWithText.h"
#include "Code/Utility/CodeGameInstance.h"
#include "../END2502.h"

void UCodeMainMenu::NativeConstruct()
{
	UGameInstance* game = GetGameInstance();
	if (!game)
	{
		UE_LOG(Game, Error, TEXT("UCodeMainMenu::NativeConstruct -> Failed to find game instance"));
		return;
	}

	UCodeGameInstance* codeGame = Cast<UCodeGameInstance>(game);
	if (!codeGame) 
	{
		UE_LOG(Game, Error, TEXT("UCodeMainMenu::NativeConstruct -> Failed to cast into UCodeGameInstance"));
		return;
	}
	
	StartGameButton->OnClickedEvent.AddDynamic(codeGame, &UCodeGameInstance::LoadFirstLevel);
	QuitGameButton->OnClickedEvent.AddDynamic(codeGame, &UCodeGameInstance::QuitTheGame);
}
