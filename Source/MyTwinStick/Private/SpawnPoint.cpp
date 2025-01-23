// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"

void ASpawnPoint::SetCurrentStatus(bool newStatus)
{
	bCurrentStatus = newStatus;
	OnStatusUpdated.Execute(bCurrentStatus, this);
}
