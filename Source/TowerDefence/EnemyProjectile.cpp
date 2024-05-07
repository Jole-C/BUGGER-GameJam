// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	EnemyMesh->SetupAttachment(RootComponent);
	EnemyMesh->SetCanEverAffectNavigation(false);
	EnemyMesh->SetCollisionProfileName("EnemyProjectile");
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

