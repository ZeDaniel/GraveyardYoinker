// Copyright Epic Games, Inc. All Rights Reserved.

#include "GraveyardYoinkerGameMode.h"
#include "GraveyardYoinkerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGraveyardYoinkerGameMode::AGraveyardYoinkerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
