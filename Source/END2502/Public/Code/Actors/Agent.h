// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "Code/Utility/EnemyInterface.h"
#include "Agent.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API AAgent : public ABaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAgent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FName TintName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FName ActionFinishedMsg;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FName HealthKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FName AmmoKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FLinearColor Color;

	virtual void PostRegisterAllComponents() override;

	virtual void EnemyAttack() override;

	virtual void EnemyReload() override;

	virtual void HandleHurt(float ratio) override;
	
private:
	UFUNCTION()
	void HandleActionFinished();

	void UpdateBlackboardHealth(float ratio);

	UFUNCTION()
	void UpdateBlackboardAmmo(float current, float max);

};
