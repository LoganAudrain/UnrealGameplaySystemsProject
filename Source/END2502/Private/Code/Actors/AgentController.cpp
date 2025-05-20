// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/AgentController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


AAgentController::AAgentController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->DetectionByAffiliation.bDetectEnemies = false;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	SightConfig->SightRadius = 900.0f;
	SightConfig->LoseSightRadius = 1100.0f;
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 300.0f;
	SightConfig->PeripheralVisionAngleDegrees = 40.0f;

	AIPerceptionComponent->ConfigureSense(*SightConfig);

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAgentController::HandlePerception);
}

void AAgentController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(BT);
}

void AAgentController::HandlePerception(AActor* Actor, FAIStimulus Stimulus)
{
	UBlackboardComponent* blackBoard = GetBlackboardComponent();

	if (Stimulus.WasSuccessfullySensed())
	{
		blackBoard->SetValueAsObject(playerKey, Actor);
	}
	else
	{
		blackBoard->ClearValue(playerKey);
	}
}
