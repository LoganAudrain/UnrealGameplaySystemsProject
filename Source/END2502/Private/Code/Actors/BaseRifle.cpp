// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseRifle.h"
#include <Kismet/KismetSystemLibrary.h>
#include "../END2502.h"

// Sets default values
ABaseRifle::ABaseRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SetRootComponent(SkeletalMeshComponent);
}

// Called when the game starts or when spawned
void ABaseRifle::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* parent = GetParentActor();
	APawn* pawn = Cast<APawn>(parent);

	if (pawn)
	{ //Valid
		ParentPawn = pawn;
	}
	else
	{ //Not Valid
		UE_LOG(Game, Warning, TEXT("Code base rifle parent is a nullptr"));
		Destroy();
	}

	ReloadAmmo();
}

void ABaseRifle::UseAmmo(const float amount = 1)
{
	CurrentAmmo = (CurrentAmmo - amount < 0) ? 0 : CurrentAmmo - amount;

	OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
}

// Called every frame
void ABaseRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseRifle::Attack()
{
	if (ActionHappening || !Alive || CurrentAmmo <= 0)
		return;

	FVector location = GetSource();
	FRotator rotation = ParentPawn->GetBaseAimRotation();
	FVector scale = { 1.0, 1.0, 1.0 };
	FTransform spawnTransform(rotation, location, scale);

	FActorSpawnParameters Params;
	Params.Owner = ParentPawn->GetController();
	Params.Instigator = ParentPawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, spawnTransform, Params);

	ActionHappening = true;
	FTimerDynamicDelegate timerDelegate;
	timerDelegate.BindUFunction(this, FName("ActionStopped"));

	UKismetSystemLibrary::K2_SetTimerDelegate(timerDelegate, ResetTime, false);
	OnRifleAttack.Broadcast(this);

	UseAmmo();
}

void ABaseRifle::RequestReload()
{
	if (!ActionHappening)
	{
		ActionHappening = true;
		OnReloadStart.Broadcast();
	}
}

void ABaseRifle::ActionStopped()
{
	ActionHappening = false;
	OnActionStopped.Broadcast();
}

void ABaseRifle::ReloadAmmo()
{
	CurrentAmmo = MaxAmmo;
	OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
}

FVector ABaseRifle::GetSource() const
{
	return SkeletalMeshComponent->GetSocketLocation(WeaponSocketName);
}

