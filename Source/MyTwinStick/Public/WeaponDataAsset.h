// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponStats.h"
#include "WeaponDataAsset.generated.h"

class ABaseProjectile;
/**
 * 
 */
UCLASS(BlueprintType)
class MYTWINSTICK_API UWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "True"))
	FItemData WeaponInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "True"))
	FWeaponStats WeaponStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "True"))
	TSoftClassPtr<ABaseProjectile> Projectile;

public:
	const FWeaponStats* GetWeaponStats() { return &WeaponStats; }
	auto GetProjectile() { return Projectile; }
	const FItemData* GetInfo() { return &WeaponInfo; }
};