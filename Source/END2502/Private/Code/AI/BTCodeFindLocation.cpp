// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AI/BTCodeFindLocation.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTCodeFindLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIPawn->GetWorld());
	if (!NavSys) return EBTNodeResult::Failed;

	FVector Origin = AIPawn->GetActorLocation();
	FNavLocation RandomLocation;

	NavSys->GetRandomPointInNavigableRadius(Origin, Radius, RandomLocation);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	blackboard->SetValueAsVector("Location", RandomLocation.Location);
	
	return EBTNodeResult::Succeeded;
}
