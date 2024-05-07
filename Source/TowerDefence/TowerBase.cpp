// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"
#include "EnemyBase.h"
#include "Components/SphereComponent.h"


void ATowerBase::TowerBehaviour_Implementation()
{
}

float ATowerBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Tower damaged")));
	if (IsInvulnerable == true)
	{
		return 0;
	}

	TowerHealth -= DamageAmount;

	if (TowerHealth <= 0)
	{
		Destroy();
	}

	IsInvulnerable = true;
	GetWorld()->GetTimerManager().SetTimer(TowerInvulnerableTimerHandle, FTimerDelegate::CreateLambda([&] {IsInvulnerable = false; }), TowerInvulnerableSeconds, false);

	return DamageAmount;
}

void ATowerBase::ParseTowerParamsForLevel()
{
	if (ParametersDataTable == nullptr)
	{
		return;
	}

	TArray<FName> TowerLevels;
	TowerLevels.Add(FName(TEXT("Level_1")));
	TowerLevels.Add(FName(TEXT("Level_2")));
	TowerLevels.Add(FName(TEXT("Level_3")));
	TowerLevels.Add(FName(TEXT("Level_4")));
	TowerLevels.Add(FName(TEXT("Level_5")));
	TowerLevels.Add(FName(TEXT("Level_6")));
	TowerLevels.Add(FName(TEXT("Level_7")));
	TowerLevels.Add(FName(TEXT("Level_8")));
	TowerLevels.Add(FName(TEXT("Level_9")));
	TowerLevels.Add(FName(TEXT("Level_10")));

	TowerLevel = FMath::Clamp(TowerLevel, 1, 10);
	TowerParams = ParametersDataTable->FindRow<FTowerParams>(TowerLevels[TowerLevel], "");

	UpgradeCost = TowerParams->UpgradeCost;
	AttackRange = TowerParams->AttackRange;
	Damage = TowerParams->Damage;
	AttackSpeed = TowerParams->AttackSpeed;
	TowerHealth = TowerParams->Health;
	EnemyDetectionRadius->SetWorldScale3D(FVector(AttackRange * 10, AttackRange * 10, AttackRange * 10));

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Upgrade Cost: %f"), UpgradeCost));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Attack Range: %f"), AttackRange));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Damage: %f"), Damage));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Attack Speed: %f"), AttackSpeed));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Health: %f"), TowerHealth));

}

FTowerParams ATowerBase::GetTowerParams()
{
	return *TowerParams;
}

void ATowerBase::UpgradeTower()
{
	TowerLevel += 1;
	ParseTowerParamsForLevel();
}

// Sets default values
ATowerBase::ATowerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	EnemyDetectionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Enemy Detection Radius"));
	EnemyDetectionRadius->SetupAttachment(RootComponent);
	EnemyDetectionRadius->SetCollisionProfileName("EnemyDetection");

	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	TowerMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();
	ParseTowerParamsForLevel();
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors,AEnemyBase::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		auto tobj = Cast<AEnemyBase>(Actor);
		OverlappingEnemies.Add(tobj);		
	}

	if (OverlappingEnemies.Num() > 0)
	{
		TowerBehaviour();
	}

	OverlappingEnemies.Empty();
}

void ATowerBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

