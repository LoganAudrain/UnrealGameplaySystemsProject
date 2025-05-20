// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../END2502.h"
#include "UObject/ConstructorHelpers.h" // bad habit, do not replicate
#include <Kismet/GameplayStatics.h>

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);
	//SphereCollision->SetEnableGravity(true); //defaults to on, just use this for debug

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetCollisionProfileName("NoCollision");
	SphereMesh->SetupAttachment(SphereCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->MaxSpeed = 1900;
	ProjectileMovement->InitialSpeed = ProjectileMovement->MaxSpeed;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	// 1) Right click delagate and go to declaration
	// 2) right click the type and go to the declaration
	// 3) ctrl c on the back of the macro based on how many inputs is declared
	// 4) create new function with same function signature
	// 5) remove extra commas
	// 6) define new function
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::HandleOverlap);
	//NOTE that input to "AddDyanamic" is the same as "CreateEvent" in blueprint


	///* Bad code, do not replicate */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> 
		Asset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	SphereMesh->SetStaticMesh(Asset.Object);
	///* Bad code end */
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->SetWorldScale3D(Scale);
	
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &Super::K2_DestroyActor, DestroyTime);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerController, this, nullptr);

	if (OtherActor && OtherActor != this && OtherComp)
		Destroy();
}

