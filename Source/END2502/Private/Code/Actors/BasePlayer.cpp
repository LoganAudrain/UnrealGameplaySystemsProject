// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Code/Utility/HealthComponent.h"
#include "PlayerHud.h"
#include "../END2502.h"

ABasePlayer::ABasePlayer()
{
	springArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	springArm->SetRelativeLocation(FVector(0.0, 80.0, 90.0));
	springArm->TargetArmLength = 205.0f;

	springArm->SetupAttachment(GetRootComponent() /*, only used if using a socket*/);
	camera->SetupAttachment(springArm);
}

FRotator ABasePlayer::GetBaseAimRotation() const
{
	return FRotationMatrix::MakeFromX(PlayerHUD->GetDestination() - WeaponObject->GetSource()).Rotator();
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		UE_LOG(Game, Error, TEXT("Failed to cast into player controller"));
		Destroy();
	}

	if (!HUDClass)
	{
		UE_LOG(Game, Error, TEXT("ABasePlayer::BeginPlay - Could not find the player hud class"));
		Destroy();
	}

	if (!WeaponObject)
	{
		UE_LOG(Game, Error, TEXT("ABasePlayer::BeginPlay - Could not find player weapon obj"));
		Destroy();
	}

	PlayerHUD = CreateWidget<UPlayerHud>(PlayerController, HUDClass);
	PlayerHUD->AddToViewport();

	HealthComponent->GetOnHurtDelegate().AddDynamic(PlayerHUD, &UPlayerHud::SetHealth);
	WeaponObject->GetOnAmmoChanged().AddDynamic(PlayerHUD, &UPlayerHud::SetAmmo);

	WeaponObject->ReloadAmmo();

	HealthComponent->GetOnHealDelegate().AddDynamic(PlayerHUD, &UPlayerHud::SetHealth);
}

void ABasePlayer::HandleDeathStart(float NotUsed)
{
	Super::HandleDeathStart(NotUsed);
	PlayerHUD->SetHealth(NotUsed);

	DisableInput(PlayerController);
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent)
	{
		UE_LOG(Game, Error, TEXT("PlayerInputComponent is a nullptr. Aborting"));
		Destroy();
		return;
	}

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	springArm->bUsePawnControlRotation = true;
	
	/* Camera Movement */
	PlayerInputComponent->BindAxis("TurnRight", this, &Super::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &Super::AddControllerPitchInput);

	/* Player Movement */
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveFowardInput);
	PlayerInputComponent->BindAxis("Strafe", this, &ABasePlayer::MoveStrafeInput);

	PlayerInputComponent->BindAction("AttackInput", EInputEvent::IE_Pressed, this, &ABasePlayer::AttackInput);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ABasePlayer::RequestReloadWrapper);
}

bool ABasePlayer::CanPickupHealth()
{
	return true;
}

void ABasePlayer::MoveFowardInput(float axisValue)
{
	AddMovementInput(FRotator(0.0, GetControlRotation().Yaw, 0.0).Vector(), axisValue);
}

void ABasePlayer::MoveStrafeInput(float axisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0, GetControlRotation().Yaw, 0.0)).GetScaledAxis(EAxis::Y), axisValue);
}

void ABasePlayer::AttackInput()
{
	WeaponObject->Attack();
	//CharacterAnimation->FireAnimation(); replaced by delagate system in BaseCharacter
}

void ABasePlayer::RequestReloadWrapper()
{
	WeaponObject->RequestReload();
}
