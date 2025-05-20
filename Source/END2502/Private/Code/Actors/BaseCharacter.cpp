// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseCharacter.h"
#include "Code/Utility/HealthComponent.h"
#include "CharacterAnimation.h"
#include "../END2502.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->SetRelativeRotation(FRotator(0.0, 270.0, 0.0));
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -90.0));

	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Child Actor Component"));
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	
	if (SkeletalMesh)
	{
		ChildActorComponent->SetupAttachment(SkeletalMesh, "PlaceWeaponHere");
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Failed to find skeletal mesh component"));
		Destroy();
	}

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	/* Set Weapon Object */

	ChildActorComponent->SetChildActorClass(WeaponClass);
	ChildActorComponent->CreateChildActor();

	WeaponObject = Cast<ABaseRifle>(ChildActorComponent->GetChildActor());
	if (WeaponObject)
	{
		//do something prob
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Failed to cast child actor into weapon obj"));
		Destroy();
	}
	
	/* Set Character Animation */
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	UAnimInstance* animInstance = SkeletalMesh->GetAnimInstance();
	UCharacterAnimation* animTemp = Cast<UCharacterAnimation>(animInstance);
	if (animTemp)
	{
		CharacterAnimation = animTemp;
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Failed to cast to UCharacterAnimation"));
		Destroy();
	}

	/* Bind to rifle delagate */
	WeaponObject->GetOnRifleAttack().AddDynamic(this, &ABaseCharacter::PlayFireAnimation);

	/* Bind Take Dmg Anim */
	HealthComponent->GetOnHurtDelegate().AddDynamic(this, &ABaseCharacter::HandleHurt);

	/* Bind Death Anim */
	HealthComponent->GetOnDeathDelegate().AddDynamic(this, &ABaseCharacter::HandleDeathStart);

	/* Bind ActionStopped After Reload */
	CharacterAnimation->OnReloadEnded.AddDynamic(WeaponObject, &ABaseRifle::ActionStopped);

	/* Bind Reload Anim With Reload Function */
	CharacterAnimation->OnReloadNow.AddDynamic(WeaponObject, &ABaseRifle::ReloadAmmo);

	/* Bind Reload Start */
	WeaponObject->GetOnReloadStart().AddDynamic(CharacterAnimation, &UCharacterAnimation::ReloadAnimation);
}

void ABaseCharacter::PlayFireAnimation(AActor* Rifle)
{
	if (Rifle == WeaponObject) //make sure that calling obj is our rifle instance
	{
		if (CharacterAnimation)
		{
			CharacterAnimation->FireAnimation();
		}
	}
}

void ABaseCharacter::HandleDeathStart(float NotUsed)
{
	CharacterAnimation->DeathAnimation(NotUsed);
	SetActorEnableCollision(false);

	WeaponObject->OwnerDied();
}

void ABaseCharacter::HandleHurt(float ratio)
{
	CharacterAnimation->HitAnimation(ratio);
}

bool ABaseCharacter::CanPickupHealth()
{
	return false;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

