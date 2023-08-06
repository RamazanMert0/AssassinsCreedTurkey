// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssassinsCreedTurkeyGameMode.h"
#include "AssassinsCreedTurkeyCharacter.h"
#include "Character_PC.h"
#include "UObject/ConstructorHelpers.h"

AAssassinsCreedTurkeyGameMode::AAssassinsCreedTurkeyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
