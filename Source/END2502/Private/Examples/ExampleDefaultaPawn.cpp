

#include "Examples/ExampleDefaultaPawn.h"
#include "../END2502.h"
#include "Examples/ExampleActorWithInterface.h"
#include "Examples/ExampleInterfaceTwo.h"
#include "Examples/ExampleInterfaceThree.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerInput.h"

// Sets default values
AExampleDefaultaPawn::AExampleDefaultaPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExampleDefaultaPawn::BeginPlay()
{
	//////////////////// END
	Super::BeginPlay();
	
	// Up Cast
	AActor* actor = this;

	// Down Cast
	APawn* pawn = Cast<APawn>(actor);

	if (pawn)
	{ //Valid
		UE_LOG(Game, Warning, TEXT("Actor is %s"), *pawn->GetName());
	}
	else
	{ //Not Valid
		UE_LOG(Game, Log, TEXT("Numbers are %d or %f"), 4, 7.3f);
	}

	UE_LOG(Game, Error, TEXT("Velocity is %s"), *GetVelocity().ToString());

	UE_LOG(Game, Warning, TEXT("It is %s"), true ? TEXT("TRUE") : TEXT("FALSE"));

	////////////////////////////////// GAR
	for (TActorIterator<AExampleActorWithInterface> it(GetWorld()); it; ++it)
	{
		actor = *it;

		/* cannot cast with u interfaces */
		UExampleInterface* U = Cast<UExampleInterface>(actor);
		if (U)
		{
			UE_LOG(Game, Log, TEXT("In the U cast"));
		}

		// this is the proper way to use an interface
		IExampleInterface* I = Cast<IExampleInterface>(actor);
		if (I)
		{
			I->TestFunction();
			UE_LOG(Game, Log, TEXT("In the I cast"));
		}

		////////////////////// GAR Lecture 4

		//Cast does not work with blueprint implementable events
		IExampleInterfaceTwo* I2 = Cast<IExampleInterfaceTwo>(actor);
		if (I2)
		{
			I2->BlueprintImplementableEvent();
			UE_LOG(Game, Log, TEXT("In the I2 cast"));
		}

		//This is how you propery use a Blueprint Implementable Event (Using implements and passing the U class interface)
		if (actor->Implements<UExampleInterfaceTwo>())
		{
			IExampleInterfaceTwo::Execute_BlueprintImplementableEvent(actor);
			UE_LOG(Game, Log, TEXT("In the I2 Implements"));
		}

		IExampleInterfaceThree* I3 = Cast<IExampleInterfaceThree>(actor);
		if (I3)
		{
			//I3->Execute_BlueprintNativeEvent(actor);
			IExampleInterfaceThree::Execute_BlueprintNativeEvent(actor);
			UE_LOG(Game, Log, TEXT("In the I3 cast"));
		}
	}
}

void AExampleDefaultaPawn::Spawn()
{
	FActorSpawnParameters Params;
	Params.Instigator = this;
	GetWorld()->SpawnActor<AActor>(spawnBlueprintClass, GetTransform(), Params);
}

// Called every frame
void AExampleDefaultaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AExampleDefaultaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// we do not need to move the project settings here
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("TEST_SPAWN", EKeys::SpaceBar));

	PlayerInputComponent->BindAction("TEST_SPAWN", EInputEvent::IE_Pressed, this, &AExampleDefaultaPawn::Spawn);
}

