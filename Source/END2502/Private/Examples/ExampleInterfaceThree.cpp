// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExampleInterfaceThree.h"
#include "../END2502.h"

// Add default functionality here for any IExampleInterfaceThree functions that are not pure virtual.

void IExampleInterfaceThree::BlueprintNativeEvent_Implementation()
{
	UE_LOG(Game, Log, TEXT("In C++: IExampleInterfaceThree::BlueprintNativeEvent_Implementation (Grandparent)"));
}
