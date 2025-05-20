// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Utility/AnimNotify_ReloadNow.h"
#include "CharacterAnimation.h"
#include "../END2502.h"

void UAnimNotify_ReloadNow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    UCharacterAnimation* AnimInstance = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance());
    if (AnimInstance)
    {
        AnimInstance->OnReloadNow.Broadcast();
    }
    else
        UE_LOG(Game, Error, TEXT("UAnimNotify_ReloadNow::Notify - Failed to cast into character animation"))
}
