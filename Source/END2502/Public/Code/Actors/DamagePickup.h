// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BasePickup.h"
#include "DamagePickup.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API ADamagePickup : public ABasePickup
{
	GENERATED_BODY()
	
public:
	ADamagePickup();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	class UParticleSystemComponent* ParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	float Damage;

	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;
	virtual void PostPickup() override;
};
