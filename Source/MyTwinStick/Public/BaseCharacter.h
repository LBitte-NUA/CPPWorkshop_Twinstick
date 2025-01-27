// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "BaseCharacter.generated.h"


UCLASS(Abstract)
class MYTWINSTICK_API ABaseCharacter : public ACharacter 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	//The Health Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "True"))
	class UHealthComponent* HealthComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "True"))
	class UWeaponComponent* WeaponComponent = nullptr;

public:
	// Our Attack/Reload Functions which can be called and overwritten in BP
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Attack();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();

protected:
	// Internal Attack/Reload functions that exists solely in C++
	virtual void Attack_Internal();

	virtual void Reload_Internal();
};
