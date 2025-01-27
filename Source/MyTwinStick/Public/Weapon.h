// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

struct FWeaponStats;
struct FItemData;
class UWeaponDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponFiredSignature, int32, newAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponReloadBeginSignature, float, ReloadTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponReloadEndSignature, int32, newClip);

UCLASS()
class MYTWINSTICK_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Weapons", meta = (WorldContext = "WorldContextObject"))
	static AWeapon* CreateWeapon(const UObject* WorldContextObject, AActor* WeaponOwner, UWeaponDataAsset* WeaponTemplate);

private:
	// Default Weapon Property Data
	const FWeaponStats* Stats; // Weapon Stats (Damage, Fire Rate, etc.)
	TSubclassOf<class ABaseProjectile> Projectile; // Projectile created by our weapon
	const FItemData* Info; // Item Data (Name, Description)
public:
	FORCEINLINE auto GetWeaponInfo() { return Info; }


public:
	void Fire(); // fire the gun
	UPROPERTY(BlueprintAssignable)
	FOnWeaponFiredSignature OnWeaponFired;
private:
	void Fire_Internal();
	void SpawnBullet();

private: /**********  Fire Rate Functionality  ***********/
	
	bool bCanFire = true;
	void ResetCanFire() { bCanFire = true; }
	FTimerHandle FireHandle;
	 
		 
public:  /**********  Reload Functionality  **************/
	void Reload();
	UPROPERTY(BlueprintAssignable)
	FOnWeaponReloadBeginSignature OnWeaponReloadBegin;
	UPROPERTY(BlueprintAssignable)
	FOnWeaponReloadEndSignature OnWeaponReloadEnd;
private:
	bool isReloading = false;
	void Reload_Internal();
	int32 Clip;
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetCurrentClip() { return Clip; }
private:
	FTimerHandle ReloadHandle;

	bool bReleasedFire = true;
	FTimerHandle ReleaseHandle;

};