// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/OverlapInfo.h>
#include "BasePickup.generated.h"

UCLASS(Abstract)
class END2502_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	class UBoxComponent* BoxCollision;

	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult);
	virtual void PostPickup();

	virtual bool CanPickup(AActor* OtherActor);

public:	
	
	UFUNCTION()
	void BoundOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
