// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/HealthPickup.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Code/Utility/PickupInterface.h"
#include "../END2502.h"

AHealthPickup::AHealthPickup()
	: Super()
{
	Damage = -1.5f;

	BoxCollision->SetRelativeScale3D(FVector(1.5f, 1.5f, 2.0f));

	ParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
	ParticleSystem->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.7f));
}

void AHealthPickup::PostPickup()
{
	Super::Super::PostPickup(); 
}

bool AHealthPickup::CanPickup(AActor* OtherActor)
{
	IPickupInterface* interface = Cast<IPickupInterface>(OtherActor);
	if (interface)
	{
		return interface->CanPickupHealth();
	}

	UE_LOG(Game, Error, TEXT("AHealthPickup::CanPickup - Failed to cast actor into interface"));
	return false;
}
