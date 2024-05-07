// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "TowerBase.h"
#include "TowerPlayerBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

void AEnemyBase::EnemyRangedBehaviour_Implementation()
{
}

void AEnemyBase::EnemyCloseBehaviour_Implementation()
{
}

void AEnemyBase::EnemyMovementBehaviour_Implementation()
{
}

float AEnemyBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Enemy damaged")));
	if (IsInvulnerable == true)
	{
		return 0;
	}

	EnemyHealth -= DamageAmount;

	if (EnemyHealth <= 0)
	{
		Destroy();
	}

	IsInvulnerable = true;
	GetWorld()->GetTimerManager().SetTimer(EnemyInvulnerableTimerHandle, FTimerDelegate::CreateLambda([&] {IsInvulnerable = false; }), EnemyInvulnerableSeconds, false);

	return DamageAmount;
}

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	EnemyMesh->SetupAttachment(RootComponent);
	EnemyMesh->SetCanEverAffectNavigation(true);
	EnemyMesh->SetCollisionProfileName("Enemy");
	TowerDetectionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Tower Detection Radius"));
	TowerDetectionRadius->SetupAttachment(RootComponent);
	TowerDetectionRadius->SetCollisionProfileName("TowerDetection");
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	MovementComponent->bConstrainToPlane = true;
	MovementComponent->bSnapToPlaneAtStart = true;
	MovementComponent->ConstrainNormalToPlane(FVector(0, 0, 1));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	EnemyHealth = MaxEnemyHealth;

	BaseReference = Cast<ATowerPlayerBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ATowerPlayerBase::StaticClass()));
}

void AEnemyBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(IsValid(this))
	{
		GetWorldTimerManager().ClearAllTimersForObject(this);
	}
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int Distance = FVector::Distance(GetActorLocation(), FVector(0, 0, 0));

	if(BaseReached == true)
	{
		EnemyCloseBehaviour();
	}
	else
	{
		EnemyRangedBehaviour();
	}

	EnemyMovementBehaviour();
	SetActorRotation(MovementComponent->Velocity.GetSafeNormal().Rotation());

	OverlappingTowers.Empty();
}

