// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

struct FWeaponStats;
class UWeaponDataAsset;

UCLASS()
class MYTWINSTICK_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	static AWeapon* CreateWeapon(AActor* WeaponOwner, UWeaponDataAsset* WeaponTemplate);

private:
	const FWeaponStats* Stats;
	TSubclassOf<class ABaseProjectile> Projectile;

public:
	void Fire(); // fire the gun

private:
	void Fire_Internal();
	void SpawnBullet();

private: /**********  Fire Rate Functionality     ********/
	
	bool bCanFire = true;
	void ResetCanFire() { bCanFire = true; }
	FTimerHandle FireHandle;

};