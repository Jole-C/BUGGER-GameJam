#include "WaveManager.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "EnemyBase.h"
#include <Kismet/GameplayStatics.h>

void AWaveManager::StartWave()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Starting Wave: %f"), (float)CurrentWaveIndex));
	OverrideWaveReset = false;
	CurrentWave = Waves[CurrentWaveIndex];
	CurrentSpawnOpportunity = 0;

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Sampled point for wave start: %f"), SampleCurveAlongPoint(CurrentWave->TimeBetweenSpawningAnEnemy)));

	GetWorld()->GetTimerManager().SetTimer(
		EnemySpawnTimerHandle,
		this,
		&AWaveManager::SpawnEnemies,
		SampleCurveAlongPoint(CurrentWave->TimeBetweenSpawningAnEnemy),
		false,
		0
	);

	InitialSpawnAngle = FMath::DegreesToRadians(FMath::RandRange(0, 360));
}

// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWaveManager::SpawnEnemies()
{
	//First figure out the number of enemies to spawn
	int NumberOfEnemiesToSpawn = SampleCurveAlongPoint(CurrentWave->EnemiesToSpawnPerSpawnOpportunity);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Sampled point for number of enemies: %f"), (float)NumberOfEnemiesToSpawn));
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Current Spawn Opportunity: %f"), (float)CurrentSpawnOpportunity));
	
	for (int i = 0; i < NumberOfEnemiesToSpawn; i++)
	{
		//Then figure out where to spawn the enemies
		float SpawnAngleAddition = SampleCurveAlongPoint(CurrentWave->EnemySpawnAngleCurve) * 360;
		float SpawnAngle = FMath::DegreesToRadians(FMath::RandRange(-SpawnAngleAddition, SpawnAngleAddition));

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Sampled angle for enemy spawn: %f"), SpawnAngle));
		int SpawnDistance = FMath::RandRange(MinEnemySpawnRadius, MaxEnemySpawnRadius);
		
		FVector SpawnPos;
		SpawnPos.X = cos(SpawnAngle) * SpawnDistance;
		SpawnPos.Y = sin(SpawnAngle) * SpawnDistance;
		SpawnPos.Z = 10;

		//Then pick the enemy to spawn
		TSubclassOf<AEnemyBase> EnemyClass = CurrentWave->EnemiesToSpawn[FMath::RandRange(0, CurrentWave->EnemiesToSpawn.Num() - 1)];
		GetWorld()->SpawnActor<AEnemyBase>(EnemyClass, SpawnPos, FRotator());
	}

	CurrentSpawnOpportunity += 1;

	GetWorld()->GetTimerManager().SetTimer(
		EnemySpawnTimerHandle,
		this,
		&AWaveManager::SpawnEnemies,
		SampleCurveAlongPoint(CurrentWave->TimeBetweenSpawningAnEnemy),
		false
	);

	if (CurrentSpawnOpportunity > CurrentWave->SpawnOpportunities)
	{
		CurrentWaveIndex += 1;
		GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimerHandle);

		GetWorld()->GetTimerManager().SetTimer(
			NextWaveTimerHandle,
			this,
			&AWaveManager::StartWave,
			CurrentWave->TimeUntilNextWave,
			false
		);
	}
}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentSpawnOpportunity == CurrentWave->SpawnOpportunities && CurrentWaveIndex == Waves.Num() - 1)
	{
		GetWorld()->GetTimerManager().ClearTimer(NextWaveTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimerHandle);
		return;
	}

	if (CurrentSpawnOpportunity > CurrentWave->SpawnOpportunities)
	{
		TArray<AActor*> Enemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), Enemies);
		
		if (Enemies.Num() == 0 && OverrideWaveReset == false)
		{
			OverrideWaveReset = true;
			CurrentWaveIndex += 1;

			GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimerHandle);
			GetWorld()->GetTimerManager().ClearTimer(NextWaveTimerHandle);
			StartWave();
		}
	}
}

float AWaveManager::SampleCurveAlongPoint(UCurveFloat* CurveToSample)
{
	if (IsValid(CurveToSample))
	{
		return CurveToSample->GetFloatValue((float)CurrentSpawnOpportunity / (float)CurrentWave->SpawnOpportunities);
	}

	return 0.0f;
}

