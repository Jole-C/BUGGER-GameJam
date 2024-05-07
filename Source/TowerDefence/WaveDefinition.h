// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveDefinition.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API UWaveDefinition : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Wave Curves", meta = (ToolTip = "Over the course of the wave, the maximum angle (+/-) will increase by this amount at this point along the curve."))
	UCurveFloat* EnemySpawnAngleCurve;

	UPROPERTY(EditAnywhere, Category = "Wave Curves", meta = (ToolTip = "When a spawn opportunity occurs, spawn the enemy at this point along the curve."))
	UCurveFloat* EnemiesToSpawnPerSpawnOpportunity;

	UPROPERTY(EditAnywhere, Category = "Wave Curves", meta = (ToolTip = "When an enemy is spawned, the curve will be sampled along this point to decide the next time until an enemy spawns, in seconds."))
	UCurveFloat* TimeBetweenSpawningAnEnemy;

	UPROPERTY(EditAnywhere, Category = "Wave Parameters", meta = (ToolTip = "When the wave is over, wait this long until the next wave, regardless of enemies."))
	int TimeUntilNextWave = 15;
	
	UPROPERTY(EditAnywhere, Category = "Wave Parameters", meta = (ToolTip = "Spawn these enemies over the wave."))
	TArray<TSubclassOf<class AEnemyBase>> EnemiesToSpawn;

	UPROPERTY(EditAnywhere, Category = "Wave Parameters", meta = (ToolTip = "Over the course of the wave, enemies will be spawned this many times."))
	int SpawnOpportunities = 10;
};
