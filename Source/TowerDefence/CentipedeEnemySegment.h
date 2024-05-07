// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "CentipedeEnemySegment.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API ACentipedeEnemySegment : public AEnemyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Behaviour")
	AActor* Follower;

	void SetFollower(AActor* NewFollower) { Follower = NewFollower; }

protected:
	void Tick(float DeltaSeconds) override;

};
