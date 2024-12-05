// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class UWeaponDataAsset;
class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYTWINSTICK_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
	UWeaponDataAsset* DefaultWeapon;

private:
	AWeapon* Weapon;

public:
	AWeapon* GetWeapon() { return Weapon; }
	void SetWeapon(AWeapon* weapon) { Weapon = weapon; }

	void FireWeapon();
};
