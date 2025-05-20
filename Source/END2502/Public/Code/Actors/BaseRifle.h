// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRifle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRifleAttackDelegate, AActor*, Rifle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRifleActionDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAmmoChangedDelegate, float, Current, float, Max);

UCLASS()
class END2502_API ABaseRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseRifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	APawn* ParentPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FName WeaponSocketName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	bool ActionHappening;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float ResetTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float CurrentAmmo;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FRifleAttackDelegate OnRifleAttack;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FRifleActionDelegate OnActionStopped;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FRifleActionDelegate OnReloadStart;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FAmmoChangedDelegate OnAmmoChanged;

	void UseAmmo(const float amount);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE FRifleAttackDelegate& GetOnRifleAttack() { return OnRifleAttack; };
	FORCEINLINE FRifleActionDelegate& GetOnActionStopped() { return OnActionStopped; };
	FORCEINLINE FRifleActionDelegate& GetOnReloadStart() { return OnReloadStart; };
	FORCEINLINE FAmmoChangedDelegate& GetOnAmmoChanged() { return OnAmmoChanged; };

	float GetMaxAmmo() const { return MaxAmmo; };
	void SetMaxAmmo(const float& ammo) { MaxAmmo = ammo; };

	void Attack();

	UFUNCTION()
	void RequestReload();

	UFUNCTION()
	void ActionStopped();

	UFUNCTION()
	void ReloadAmmo();

	UFUNCTION(BlueprintCallable)
	FVector GetSource() const;

	UFUNCTION(BlueprintCallable)
	void OwnerDied() { Alive = false; };

private:
	bool Alive = true;
};
