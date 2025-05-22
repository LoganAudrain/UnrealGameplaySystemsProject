// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWithText.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonActionDelegate);

/**
 * 
 */
UCLASS()
class END2502_API UButtonWithText : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BackgroundButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Information;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FText Info;

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

public:
	UPROPERTY(BlueprintAssignable, Category = Default)
	FButtonActionDelegate OnClickedEvent;

private:
	UFUNCTION()
	void HandleClicked();
};
