// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

// Abstract Property 'hides' the C++ Class from the editor. Only derived classes are seen.
UCLASS(Abstract)
class MYTWINSTICK_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = "True"))
	class USphereComponent* Collider;

	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = "True"))
	class UProjectileMovementComponent* Movement;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, 
					AActor* OtherActor, 
					UPrimitiveComponent* OtherComp, 
					int32 OtherBodyIndex, 
					bool bFromSweep, 
					const FHitResult& SweepResult);
};
