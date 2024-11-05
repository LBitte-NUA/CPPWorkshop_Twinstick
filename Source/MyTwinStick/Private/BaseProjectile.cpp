// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DamageInterface.h"

// Define ECC_Projectile as a pre existing Engine Collision Channel
#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel1

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlap);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Collider->SetCollisionObjectType(ECC_Projectile);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	Movement->InitialSpeed = 500.f;
	Movement->ProjectileGravityScale = 0.f;
	Movement->SetUpdatedComponent(Collider);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called on our Projectile Collision Overlapping with 'something'
void ABaseProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) { return; } // Return if Invalid Hit

	if (OtherActor == GetOwner()) { return; } // Return if Hit Actor is Owner

	if (OtherActor->Implements<UDamageInterface>())
	{
		IDamageInterface::Execute_ApplyDamage(OtherActor, GetOwner(), FMath::RandRange(5, 10));

		//float health = IDamageInterface::Execute_GetHealth(OtherActor);
		//UE_LOG(LogTemp, Warning, TEXT("Health: %f"), health);
	}
}



