// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExampleInterface.h"
#include "../END2502.h"

// Add default functionality here for any IExampleInterface functions that are not pure virtual.

void IExampleInterface::BlueprintCallable()
{
	UE_LOG(Game, Log, TEXT("In c++ IExampleInterface::BlueprintCallable"));
}
