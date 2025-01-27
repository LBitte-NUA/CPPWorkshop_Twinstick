// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class UWeaponDataAsset;
class AWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYTWINSTICK_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWeaponDataAsset> DefaultWeapon;

private:
	// Current Weapon Held
	TObjectPtr<AWeapon> Weapon;

public:
	UFUNCTION(BlueprintCallable)
	void SetDefaultWeapon(UWeaponDataAsset* newDefaultWeapon);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UWeaponDataAsset* GetDefaultWeapon() { return DefaultWeapon; }

public:
	// Getter and Setter for Weapon
	UFUNCTION(BlueprintPure)
	AWeapon* GetWeapon() { return Weapon; }
	void SetWeapon(AWeapon* weapon) { Weapon = weapon; }

	// Tell weapon to Fire
	void FireWeapon();
	// Tell Weapon to Reload
	void ReloadWeapon();

public:
	// Replace current weapon with new weapon actor.
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AWeapon* newWeapon);

};
