// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerDefenceGameMode.h"
#include "TowerDefenceCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATowerDefenceGameMode::ATowerDefenceGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
