// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Examples/ExampleInterface.h"
#include "Examples/ExampleInterfaceThree.h"
#include "ExampleActorWithInterface.generated.h"


UCLASS()
class END2502_API AExampleActorWithInterface : public AActor, 
	public IExampleInterface, 
	public IExampleInterfaceThree
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExampleActorWithInterface();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//----------------------------------------//
	// IExampleInterface
	//----------------------------------------//

	virtual void TestFunction() override;

	//----------------------------------------//
	// IExampleInterfaceThre
	//----------------------------------------//

	virtual void BlueprintNativeEvent_Implementation() override;
};
