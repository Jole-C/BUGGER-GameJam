// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "CentipedeEnemySegment.h"
#include "CentipedeEnemyHead.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API ACentipedeEnemyHead : public AEnemyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Behaviour")
	int NumberOfSegments = 5;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Behaviour")
	TSubclassOf<ACentipedeEnemySegment> SegmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Behaviour")
	TSubclassOf<ACentipedeEnemySegment> TailClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<ACentipedeEnemySegment*> Segments;
};
