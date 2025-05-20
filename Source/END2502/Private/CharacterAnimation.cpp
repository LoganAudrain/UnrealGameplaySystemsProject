// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimation.h"
#include "KismetAnimationLibrary.h"
#include "../END2502.h"

void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* pawn = TryGetPawnOwner();
	if (pawn)
	{
		Velocity = pawn->GetVelocity().Size();
		Direction = UKismetAnimationLibrary::CalculateDirection(pawn->GetVelocity(), pawn->GetActorRotation());
	}
	else
	{
		PreviewWindowUpdate();
	}

	ActionSlotName = "Action";
}

void UCharacterAnimation::PreviewWindowUpdate_Implementation()
{
	//in the bp version it called a parent function which i assume is this

	if (DebugFire)
	{
		DebugFire = false;
		FireAnimation();
	}

	if (DebugHit)
	{
		DebugHit = false;
		HitAnimation(0.0f);
	}

	if (DebugDeath)
	{
		DebugDeath = false;
		DeathAnimation(0.0f);
	}

	if (DebugReload)
	{
		DebugReload = false;
		ReloadAnimation();
	}
}

void UCharacterAnimation::FireAnimation()
{
	PlaySlotAnimationAsDynamicMontage(FireAsset, ActionSlotName);
}

void UCharacterAnimation::HitAnimation(float NotUsed)
{
	PlaySlotAnimationAsDynamicMontage(HitAsset, ActionSlotName);
}

void UCharacterAnimation::DeathAnimation(float NotUsed)
{
	if (DeathAssets.Num() > 0)
	{
		int32 rand = FMath::RandRange(0, DeathAssets.Num() - 1);
		CurrentDeathAsset = DeathAssets[rand];
	}
	else
		UE_LOG(Game, Error, TEXT("No death animation assets were found"));
}

void UCharacterAnimation::ReloadAnimation()
{
	PlaySlotAnimationAsDynamicMontage(ReloadAsset, ActionSlotName);
}


