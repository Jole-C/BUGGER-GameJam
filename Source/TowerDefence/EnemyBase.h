// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBase.generated.h"

UCLASS()
class TOWERDEFENCE_API AEnemyBase : public APawn
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* EnemyMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class USphereComponent* TowerDetectionRadius;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behaviour")
	TArray<class ATowerBase*> OverlappingTowers;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour")
	bool BaseReached = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Behaviour")
	int MaxEnemyHealth;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Behaviour")
	float EnemyHealth;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Behaviour")
	float EnemyInvulnerableSeconds = 1.5;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Behaviour")
	int RadiusForCloseBehaviour = 250;

	UPROPERTY(BlueprintReadOnly, Category = "Behaviour")
	class ATowerPlayerBase* BaseReference;

	UFUNCTION(BlueprintNativeEvent, Category = "Behaviour")
	void EnemyRangedBehaviour();
	void EnemyRangedBehaviour_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Behaviour")
	void EnemyCloseBehaviour();
	void EnemyCloseBehaviour_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Behaviour")
	void EnemyMovementBehaviour();
	void EnemyMovementBehaviour_Implementation();

	// Sets default values for this actor's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent,class AController* EventInstigator,AActor* DamageCauser) override;

	bool IsInvulnerable = false;
	FTimerHandle EnemyInvulnerableTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
