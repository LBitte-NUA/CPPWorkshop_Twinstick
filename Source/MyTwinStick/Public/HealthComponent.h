// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageInterface.h"

#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthModifiedSignature, float, newHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeathSignature, AActor*, Myself, AActor*, Attacker );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYTWINSTICK_API UHealthComponent : public UActorComponent, public IDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "True"))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "True"))
	float Health = MaxHealth;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& ChangedProperty) override;
#endif

public:
	void SetMaxHealth(float value) { MaxHealth = value; } // Set mmax Health
	float GetMaxHealth(){return MaxHealth;} // Get Max Health

	UFUNCTION(BlueprintCallable)
	void ResetHealth() { Health = MaxHealth; } // Reset Health to Max Health

private:
	void IncreaseHealth_Internal(float value); // increase health by value
	void DecreaseHealth_Internal(AActor* Dealer, float value); // decrease health by value

	void Death(AActor* Dealer); // Component ran out of health
		
public:
	void ApplyDamage_Implementation(AActor* Dealer, float Damage) override;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnHealthModifiedSignature OnHealthModified;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnDeathSignature OnDeath;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta =(AllowPrivateAccess = "True"))
	ETeam Team;

public:
	ETeam GetTeam_Implementation() override { return Team; }


// Health Regen

public:
	// Amount Regened Per Second
	UPROPERTY(EditAnywhere)
	float HealthRegen = 0.f;

	UPROPERTY(Editanywhere)
	float RegenResetTime = 0.f;

private:
	void StartRegen();
	void StopRegen();
	FTimerHandle RegenHandle;
	FTimerHandle RegenResetHandle;

};
