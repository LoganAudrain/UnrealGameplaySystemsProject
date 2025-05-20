// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Utility/AnimNotify_ReloadEnded.h"
#include "CharacterAnimation.h"
#include "../END2502.h"

void UAnimNotify_ReloadEnded::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

    UCharacterAnimation* AnimInstance = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance());
    if (AnimInstance)
    {
        AnimInstance->OnReloadEnded.Broadcast();
    }
    else
        UE_LOG(Game, Error, TEXT("UAnimNotify_ReloadEnded::Notify - Failed to cast into character animation"))

}
