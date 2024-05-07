// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveDefinition.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

UCLASS()
class TOWERDEFENCE_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Behaviour")
	int MinEnemySpawnRadius = 500;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Behaviour")
	int MaxEnemySpawnRadius = 800;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Behaviour")
	TArray<UWaveDefinition*> Waves;

	UFUNCTION(BlueprintCallable)
	void StartWave();

	UFUNCTION(BlueprintCallable)
	bool GameEnded() { return CurrentSpawnOpportunity == CurrentWave->SpawnOpportunities && CurrentWaveIndex == Waves.Num() - 1; }

	// Sets default values for this actor's properties
	AWaveManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnEnemies();

	UWaveDefinition* CurrentWave;
	bool OverrideWaveReset = false;
	int CurrentWaveIndex = 0;
	int CurrentSpawnOpportunity = 0;
	float InitialSpawnAngle;
	FTimerHandle EnemySpawnTimerHandle;
	FTimerHandle NextWaveTimerHandle;

	float SampleCurveAlongPoint(UCurveFloat* CurveToSample);
};
