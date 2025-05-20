// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleFunctions.generated.h"

UCLASS()
class END2502_API AExampleFunctions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExampleFunctions();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// BlueprintCallable - Lets you call functions from blueprint
	UFUNCTION(BlueprintCallable)
	void BlueprintCallable();

	//BlueprintImplementableEvent - Declared in c++, defined in blueprint
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BlueprintImplementableEvent();

	//BlueprintNativeEvent - declared in c++, defined in c++, override in blueprint
	//Note the definition must end in _Implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BlueprintNativeEvent(); //to use funtion in c++, call this one
	virtual void BlueprintNativeEvent_Implementation(); //to override in c++, call this
	// you need all three lines for a BlueprintNativeEvent

	// pure function
	UFUNCTION(BlueprintCallable)
	float PureFunction() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
