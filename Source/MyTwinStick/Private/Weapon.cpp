// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "WeaponDataAsset.h"
#include "BaseProjectile.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

AWeapon* AWeapon::CreateWeapon(AActor* WeaponOwner, UWeaponDataAsset* WeaponTemplate)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = WeaponOwner;
	AWeapon* weapon = WeaponOwner->GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), spawnParams);

	weapon->Stats = WeaponTemplate->GetWeaponStats();
	weapon->Projectile = WeaponTemplate->GetProjectile().LoadSynchronous();

	return weapon;
}

// This Function is called by the weapon holder
void AWeapon::Fire()
{
	// can we actually fire?
	if (bCanFire)
	{
		Fire_Internal();
	}
}

void AWeapon::Fire_Internal()
{
	bCanFire = false; // After firing, set canFire to false

	// Set a timer to resetcanfire after fire Interval cooldown.
	GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &AWeapon::ResetCanFire, Stats->FireInterval, false);

	for (int32 i = 1; i <= Stats->Bullets; i++)
	{
		SpawnBullet();
	}
}

void AWeapon::SpawnBullet()
{
	// create the bullet

	if (Projectile == nullptr) { return; } // Return if projectile is invalid

	// Create the Transform parameters for our projectile spawn.
	FVector Location = GetOwner()->GetActorLocation();
	FVector Direction = GetOwner()->GetActorForwardVector();
	FVector AimOffset = FVector(FMath::RandRange(-Stats->AimOffset, Stats->AimOffset), // X
								FMath::RandRange(-Stats->AimOffset, Stats->AimOffset), // Y
								0.f);												   // Z
	Direction += AimOffset;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner(); //Set the owner of the projectile to the character.

	GetWorld()->SpawnActor<ABaseProjectile>(Projectile.Get(), Location, Direction.ToOrientationRotator(), SpawnParams);
}




