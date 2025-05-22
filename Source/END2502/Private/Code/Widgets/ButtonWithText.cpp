// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Widgets/ButtonWithText.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UButtonWithText::NativeConstruct()
{
	BackgroundButton->OnClicked.AddDynamic(this, &UButtonWithText::HandleClicked);
}

void UButtonWithText::NativePreConstruct()
{
	Information->SetText(Info);
}

void UButtonWithText::HandleClicked()
{
	OnClickedEvent.Broadcast();
}
