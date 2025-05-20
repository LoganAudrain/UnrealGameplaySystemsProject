// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* CrossHair;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CurrentAmmo;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	class UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FName ColorName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FLinearColor SafeColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FLinearColor DangerColor;
	
	virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintCallable)
	void SetHealth(float percent);

	UFUNCTION(BlueprintCallable)
	FVector GetDestination() const;

	UFUNCTION(BlueprintCallable)
	void SetAmmo(float Current, float Max);

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

private:
	FVector EndPoint;
};
