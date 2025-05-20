// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimNotifyDelegate);

/**
 * 
 */
UCLASS()
class END2502_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Velocity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FName ActionSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool DebugFire = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool DebugHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool DebugDeath = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool DebugReload = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Assets")
	class UAnimSequenceBase* FireAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Assets")
	class UAnimSequenceBase* HitAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Assets")
	class UAnimSequenceBase* CurrentDeathAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Assets")
	class UAnimSequenceBase* ReloadAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Assets")
	TArray<UAnimSequenceBase*> DeathAssets;

	UFUNCTION(BlueprintNativeEvent)
	void PreviewWindowUpdate();
	virtual void PreviewWindowUpdate_Implementation();

public:

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FAnimNotifyDelegate OnReloadEnded;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FAnimNotifyDelegate OnReloadNow;

	UFUNCTION(BlueprintCallable)
	void FireAnimation();

	UFUNCTION(BlueprintCallable)
	void HitAnimation(float NotUsed);

	UFUNCTION(BlueprintCallable)
	void DeathAnimation(float NotUsed);

	UFUNCTION(BlueprintCallable)
	void ReloadAnimation();
};
