// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AgentController.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API AAgentController : public AAIController
{
	GENERATED_BODY()

public:
	AAgentController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBehaviorTree* BT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FName playerKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	class UAIPerceptionComponent* AIPerceptionComponent;

public:
	void OnPossess(APawn* InPawn) override;

private: 
	UFUNCTION()
	void HandlePerception(AActor* Actor, FAIStimulus Stimulus);
};
