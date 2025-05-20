// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Code/Actors/BaseRifle.h"
#include "CoreMinimal.h"
#include "Code/Utility/PickupInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class END2502_API ABaseCharacter : public ACharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	class UChildActorComponent* ChildActorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<AActor> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	ABaseRifle* WeaponObject;

	UFUNCTION()
	void PlayFireAnimation(AActor* Rifle);

	UFUNCTION()
	virtual void HandleDeathStart(float NotUsed);

	UFUNCTION()
	virtual void HandleHurt(float ratio);

	UFUNCTION()
	virtual bool CanPickupHealth() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	class UCharacterAnimation* CharacterAnimation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
