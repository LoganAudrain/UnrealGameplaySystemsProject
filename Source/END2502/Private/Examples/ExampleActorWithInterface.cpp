// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExampleActorWithInterface.h"
#include "../END2502.h"

// Sets default values
AExampleActorWithInterface::AExampleActorWithInterface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExampleActorWithInterface::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExampleActorWithInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExampleActorWithInterface::TestFunction()
{
	UE_LOG(Game, Log, TEXT("In c++: AExampleActorWithInterface::TestFunction"));
}

void AExampleActorWithInterface::BlueprintNativeEvent_Implementation()
{
	IExampleInterfaceThree::BlueprintNativeEvent_Implementation();
	UE_LOG(Game, Log, TEXT("AExampleActorWithInterface::BlueprintNativeEvent_Implementation (Parent)"));
}

