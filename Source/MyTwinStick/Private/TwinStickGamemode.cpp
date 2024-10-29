// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinStickGamemode.h"
#include "BaseCharacter.h"

ATwinStickGamemode::ATwinStickGamemode()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
}