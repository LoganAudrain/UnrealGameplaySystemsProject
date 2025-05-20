// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include <Blueprint/SlateBlueprintLibrary.h>


void UPlayerHud::NativeConstruct()
{
	Super::NativeConstruct();

	DynamicMaterial = CrossHair->GetDynamicMaterial();
}

void UPlayerHud::SetHealth(float percent)
{
	HealthBar->SetPercent(percent);
}

FVector UPlayerHud::GetDestination() const
{
	return EndPoint;
}

void UPlayerHud::SetAmmo(float Current, float Max)
{
	CurrentAmmo->SetText(FText::AsNumber(Current));
	MaxAmmo->SetText(FText::AsNumber(Max));
}

void UPlayerHud::NativeTick(const FGeometry& geometry, float deltaTime)
{
	Super::NativeTick(geometry, deltaTime);

	FVector2D PixelPos;
	{
		FVector2D View; //scoped this function since we dont actually need the "view" value
		USlateBlueprintLibrary::LocalToViewport(this, CrossHair->GetCachedGeometry(),
			FVector2D(0, 0), PixelPos, View);
	}

	FVector2D result = CrossHair->GetCachedGeometry().GetAbsoluteSize() * 0.5f;
	result += PixelPos;

	FVector worldDir;
	FVector worldPos;
	GetOwningPlayer()->DeprojectScreenPositionToWorld(result.X, result.Y, worldPos, worldDir);
	EndPoint = (worldDir * 100'000) + worldPos;

	/* Test for Collision */

	TArray<AActor*> ignore = { GetOwningPlayerPawn() };

	FCollisionObjectQueryParams objParams;
	objParams.AddObjectTypesToQuery(ECC_Pawn);
	objParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionQueryParams Params;
	Params.AddIgnoredActors(ignore);

	const AActor* IgnoreActor = Cast<AActor>(this);
	Params.AddIgnoredActor(IgnoreActor);

	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);

	FHitResult hitResult;
	bool const hit = World ? World->LineTraceSingleByObjectType(hitResult, worldPos, EndPoint, objParams, Params) : false;

	/* Process Collision */

	if (hit)
	{
		EndPoint = hitResult.ImpactPoint;
		
		if (hitResult.Component->GetCollisionObjectType() == EObjectTypeQuery::ObjectTypeQuery3)
			DynamicMaterial->SetVectorParameterValue(ColorName, DangerColor);
		else 
			DynamicMaterial->SetVectorParameterValue(ColorName, SafeColor);
	}
	else
	{
		DynamicMaterial->SetVectorParameterValue(ColorName, SafeColor);
	}
}
