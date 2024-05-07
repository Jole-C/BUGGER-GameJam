// Fill out your copyright notice in the Description page of Project Settings.


#include "CentipedeEnemySegment.h"

void ACentipedeEnemySegment::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsValid(Follower) == false)
	{
		Destroy();
	}
}
