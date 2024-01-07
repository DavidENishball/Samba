// Copyright Epic Games, Inc. All Rights Reserved.

#include "SambaGameMode.h"
#include "SambaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASambaGameMode::ASambaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
