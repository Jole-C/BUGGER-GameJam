// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "TowerBase.generated.h"

USTRUCT(BlueprintType)
struct FTowerParams : public FTableRowBase
{
	GENERATED_BODY();

public:
	UPROPERTY(EditDefaultsOnly)
	float UpgradeCost;

	UPROPERTY(EditDefaultsOnly)
	float AttackRange;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly)
	float AttackSpeed;

	UPROPERTY(EditDefaultsOnly)
	float Health;
};

UCLASS()
class TOWERDEFENCE_API ATowerBase : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* EnemyDetectionRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TowerMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Tower Behaviour")
	UDataTable* ParametersDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Behaviour")
	TArray<class AEnemyBase*> OverlappingEnemies;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float UpgradeCost;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AttackRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AttackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TowerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Behaviour")
	int TowerLevel = 1;

	UFUNCTION(BlueprintCallable, Category = "Tower Behaviour")
	void UpgradeTower();

	UFUNCTION(BlueprintNativeEvent, Category = "Tower Behaviour")
	void TowerBehaviour();
	void TowerBehaviour_Implementation();

	UFUNCTION(BlueprintCallable, Category = "TowerBehaviour")
	void ParseTowerParamsForLevel();

	UFUNCTION(BlueprintCallable, Category = "TowerBehaviour")
	FTowerParams GetTowerParams();

	// Sets default values for this actor's properties
	ATowerBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

protected:
	FTowerParams* TowerParams;
	bool IsInvulnerable = false;
	int TowerInvulnerableSeconds = 2;
	FTimerHandle TowerInvulnerableTimerHandle;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
