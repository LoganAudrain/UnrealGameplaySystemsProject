// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ABasePlayer();
	virtual FRotator GetBaseAimRotation() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDeathStart(float NotUsed) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	class UCameraComponent* camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UUserWidget> HUDClass;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool CanPickupHealth() override;

private:
	class UPlayerHud* PlayerHUD;
	APlayerController* PlayerController;

	void MoveFowardInput(float axisValue);
	void MoveStrafeInput(float axisValue);
	void AttackInput();
	void RequestReloadWrapper();
};
