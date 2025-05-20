// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Utility/HealthComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "../END2502.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	AActor* parent = GetOwner();

	UE_LOG(Game, Error, TEXT("Binding to OnTakeAnyDamage"));
	parent->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamage);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth -= Damage;
	UKismetMathLibrary::FClamp(CurrentHealth, 0.0, MaxHealth);
	AActor* parent = GetOwner();

	if (CurrentHealth > 0)
	{
		if (Damage > 0)
		{
			OnHurt.Broadcast(CurrentHealth / MaxHealth);
		}
		else//(Damage <= 0)
		{
			OnHeal.Broadcast(CurrentHealth / MaxHealth);
		}
	}
	else
	{
		parent->OnTakeAnyDamage.Remove(this, FName("HandleDamage"));
		OnDeath.Broadcast(0);
	}
	
}

