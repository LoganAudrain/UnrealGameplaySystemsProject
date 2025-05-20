// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDelegate, float, ratio);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class END2502_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float MaxHealth;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegate")
	FHealthDelegate OnHurt;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegate")
	FHealthDelegate OnHeal;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegate")
	FHealthDelegate OnDeath;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE FHealthDelegate& GetOnHurtDelegate() { return OnHurt; }
	FORCEINLINE FHealthDelegate& GetOnHealDelegate() { return OnHeal; }
	FORCEINLINE FHealthDelegate& GetOnDeathDelegate() { return OnDeath; }
private:
	UFUNCTION()
	void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
