// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExampleVariable.h"
#include "../END2502.h"

// Sets default values
AExampleVariable::AExampleVariable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	ClassType = AExampleVariable::StaticClass();
}

// Called when the game starts or when spawned
void AExampleVariable::BeginPlay()
{
	Super::BeginPlay();
	
	//How to bind to a delegate:
	OnDelegateInstance.AddDynamic(this, &AExampleVariable::ExampleBoundFunction);
	OnDelegateInstance.AddDynamic(this, &AExampleVariable::AnotherBoundFunction);
	OnDelegateInstance.Broadcast(this);
}

// Called every frame
void AExampleVariable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExampleVariable::ExampleBoundFunction(AActor* Actor)
{
	UE_LOG(Game, Error, TEXT("Function called by delegate"));
}

void AExampleVariable::AnotherBoundFunction(AActor* Actor)
{
	UE_LOG(Game, Error, TEXT("Another function called by delegate"));
}

