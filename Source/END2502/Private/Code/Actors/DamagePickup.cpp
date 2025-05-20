// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/DamagePickup.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h> 

ADamagePickup::ADamagePickup()
	: ABasePickup(), Damage(2.0f)
{
	BoxCollision->SetRelativeScale3D(FVector(1.6f, 1.6f, 1.6f));

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("Particle System");
	ParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, -30.0f));
	ParticleSystem->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.25f));
	ParticleSystem->SetupAttachment(GetRootComponent());
}

void ADamagePickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
	Super::HandlePickup(OtherActor, SweepResult);

	UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
}

void ADamagePickup::PostPickup()
{
	//Overriden to stop base function from destroying the actor
}
