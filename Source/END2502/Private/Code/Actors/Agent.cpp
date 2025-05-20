// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Agent.h"
#include "END2502/Public/Code/Actors/AgentController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <BrainComponent.h>
#include "../END2502.h"


AAgent::AAgent()
	: ActionFinishedMsg("ActionFinished"), HealthKey("HealthRatio"), AmmoKey("Ammo")
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAgent::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	GetMesh()->SetVectorParameterValueOnMaterials(TintName, FVector(Color));
}

void AAgent::EnemyAttack()
{
	WeaponObject->Attack();
}

void AAgent::EnemyReload()
{
	WeaponObject->RequestReload();
}

void AAgent::HandleHurt(float ratio)
{
	Super::HandleHurt(ratio);

	UpdateBlackboardHealth(ratio);
}

void AAgent::HandleActionFinished()
{
	FAIMessage::Send(this, FAIMessage(ActionFinishedMsg, this, true));
}

void AAgent::UpdateBlackboardHealth(float ratio)
{
	AAIController* aiController = Cast<AAIController>(GetController());

	if (aiController == nullptr)
	{
		UE_LOG(Game, Error, TEXT("AAgent::UpdateBlackboardHealth - Failed to cast into ai controller"));
		return;
	}

	UBlackboardComponent* bbComponent = aiController->GetBlackboardComponent();
	if (bbComponent == nullptr)
	{
		UE_LOG(Game, Error, TEXT("AAgent::UpdateBlackboardHealth - Failed to get blackboard component"));
		return;
	}

	bbComponent->SetValueAsFloat(HealthKey, ratio);
}

void AAgent::UpdateBlackboardAmmo(float current, float max)
{
	AAIController* aiController = Cast<AAIController>(GetController());

	if (aiController == nullptr)
	{
		UE_LOG(Game, Error, TEXT("AAgent::UpdateBlackboardAmmo - Failed to cast into ai controller"));
		return;
	}

	UBlackboardComponent* bbComponent = aiController->GetBlackboardComponent();
	if (bbComponent == nullptr)
	{
		UE_LOG(Game, Error, TEXT("AAgent::UpdateBlackboardAmmo - Failed to get blackboard component"));
		return;
	}

	bbComponent->SetValueAsFloat(AmmoKey, current);
}

void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAgent::BeginPlay()
{
	Super::BeginPlay();

	WeaponObject->GetOnActionStopped().AddDynamic(this, &AAgent::HandleActionFinished);
	UpdateBlackboardHealth(1.0f);

	WeaponObject->GetOnAmmoChanged().AddDynamic(this, &AAgent::UpdateBlackboardAmmo);
	WeaponObject->ReloadAmmo();
}

void AAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
