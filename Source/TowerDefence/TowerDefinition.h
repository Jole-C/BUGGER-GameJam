// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerDefinition.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API UTowerDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Tower Description", meta = (ToolTip = "The name of the tower."))
	FString TowerName;

	UPROPERTY(EditAnywhere, Category = "Tower Description", meta = (ToolTip = "The description of the tower."))
	FString TowerDescription;

	UPROPERTY(EditAnywhere, Category = "Tower Visuals", meta = (ToolTip = "The tower's asset in build mode."))
	UTexture2D* TowerAsset;

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (ToolTip = "The levels of the tower."))
	TArray<TSubclassOf<class ATowerBase>> TowerLevels;

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (ToolTip = "The cost of the tower."))
	int BaseTowerCost;

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (ToolTip = "The cost to upgrade the."))
	int TowerUpgradeCost;
};
