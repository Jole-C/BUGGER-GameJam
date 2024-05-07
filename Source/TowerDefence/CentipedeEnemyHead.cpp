// Fill out your copyright notice in the Description page of Project Settings.


#include "CentipedeEnemyHead.h"

void ACentipedeEnemyHead::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < NumberOfSegments; i++)
	{
		ACentipedeEnemySegment* NewSegment;
		FTransform SpawnTransform;
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnTransform.SetTranslation(GetActorLocation());
		SpawnTransform.SetRotation(GetActorRotation().Quaternion());

		if (i < NumberOfSegments)
		{
			NewSegment = GetWorld()->SpawnActor<ACentipedeEnemySegment>(SegmentClass, SpawnTransform, SpawnParameters);
		}
		else
		{
			NewSegment = GetWorld()->SpawnActor<ACentipedeEnemySegment>(TailClass, SpawnTransform, SpawnParameters);
		}

		if (i == 0)
		{
			NewSegment->SetFollower(this);
		}
		else
		{
			NewSegment->SetFollower(Segments[i - 1]);
		}

		Segments.Add(NewSegment);
	}
}
