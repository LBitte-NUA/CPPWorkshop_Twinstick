// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DamageInterface.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlap);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

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

void ABaseProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("HIt Something"));
	if (OtherActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor"));
		if (IDamageInterface* DamagedActor = Cast<IDamageInterface>(OtherActor))
		{
			DamagedActor->ApplyDamage(50.f);
		}

	}
}



