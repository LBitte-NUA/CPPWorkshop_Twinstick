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
	weapon->Clip = weapon->Stats->ClipSize;

	weapon->Info = WeaponTemplate->GetInfo();

	return weapon;
}

// This Function is called by the weapon holder
void AWeapon::Fire()
{
	// Check our Fire Type
	if (Stats->FireType == EW_FireType::Semi)
	{
		// Start a short timer that is reset if we hold the fire button. (Never Releases while held)
		GetWorldTimerManager().SetTimer(ReleaseHandle, FTimerDelegate::CreateLambda([&] { bReleasedFire = true; }), 0.01f, false);

		// If we haven't released fire we return.
		if (!bReleasedFire) { return; }
		// If we've released fire we can continue
		bReleasedFire = false;
	}

	// Do we have any bullets Currently?
	if (Clip == 0)
	{
		// Force Reload Attempt on firing empty gun
		Reload();
	}

	// Can we Actuall Fire?
	if (bCanFire && Clip > 0)
	{
		Fire_Internal();
	}
}

void AWeapon::Fire_Internal()
{

	bCanFire = false; // After firing, set bCanFire to false

	// Set a timer to resetcanfire after fire Interval cooldown.
	GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &AWeapon::ResetCanFire, Stats->FireInterval, false);

	// Check if we are currently reloading
	if (GetWorldTimerManager().IsTimerActive(ReloadHandle))
	{
		//Cancel the reload upon firing.
		GetWorldTimerManager().ClearTimer(ReloadHandle);
		isReloading = false;
	}

	for (int32 i = 1; i <= Stats->BulletsPerShot; i++)
	{
		SpawnBullet();
	}

	// Decrease clip amount due to firing the weapon.
	Clip--;
}

void AWeapon::SpawnBullet()
{
	// create the bullet

	if (Projectile == nullptr) { return; } // Return if projectile is invalid

	// Create the Transform parameters for our projectile spawn.
	FVector Location = GetOwner()->GetActorLocation();
	FVector Direction = GetOwner()->GetActorForwardVector();
	FVector AimOffset = FVector(FMath::RandRange(-Stats->BulletAimOffset, Stats->BulletAimOffset), // X
								FMath::RandRange(-Stats->BulletAimOffset, Stats->BulletAimOffset), // Y
								0.f);												               // Z


	Direction += AimOffset;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner(); //Set the owner of the projectile to the character.

	auto Bullet = GetWorld()->SpawnActor<ABaseProjectile>(Projectile.Get(), Location, Direction.ToOrientationRotator(), SpawnParams);
	Bullet->SetDamage(FMath::RandRange(Stats->MinDamage, Stats->MaxDamage));

}

void AWeapon::Reload()
{
	// Do nothing if we are reloading
	if (isReloading == true) { return; }

	isReloading = true;
	GetWorldTimerManager().SetTimer(ReloadHandle, this, &AWeapon::Reload_Internal, Stats->ReloadInterval, false);
	//UE_LOG(LogTemp, Warning, TEXT("Reloading"));
}

void AWeapon::Reload_Internal()
{
	switch (Stats->ReloadType)
	{
		// Reload Full Clip if reload type is Full
	case EW_ReloadType::Full:
		Clip = Stats->ClipSize;
		break;
		// Reload Single Shot if reload type is Single
	case EW_ReloadType::Single:
		if (Clip < Stats->ClipSize)
		{
			Clip++;
		}
		break;
	default:
		break;
	}

	isReloading = false;
	// If Single clip Reload, Attempt to Continue Reloading.
	if (Clip < Stats->ClipSize)
	{
		Reload();
	}
}


