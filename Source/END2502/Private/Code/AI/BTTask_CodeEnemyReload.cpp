// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AI/BTTask_CodeEnemyReload.h"
#include "AIController.h"
#include "Code/Utility/EnemyInterface.h"
#include "../END2502.h"

EBTNodeResult::Type UBTTask_CodeEnemyReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn) return EBTNodeResult::Failed;

	AActor* actor = Cast<AActor>(AIPawn);

	IEnemyInterface* interface = Cast<IEnemyInterface>(actor);
	if (interface)
	{
		interface->EnemyReload();
		OwnerComp.RegisterMessageObserver(this, ActionFinishedMsg);

		return EBTNodeResult::InProgress;
	}

	UE_LOG(Game, Warning, TEXT("Failed to cast interface in UBTTask_CodeEnemyAttack::ExecuteTask"));
	return EBTNodeResult::Failed;
}
