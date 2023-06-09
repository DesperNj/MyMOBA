// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestMobaGameMode.h"
#include "TestMobaPlayerController.h"
#include "TestMobaCharacter.h"
#include "Characters/Fisher.h"
#include "UObject/ConstructorHelpers.h"

ATestMobaGameMode::ATestMobaGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATestMobaPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	//static AFisher PlayerClas = NewObject<AFisher>();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GameCharacters/cFisher"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		//DefaultPawnClass = AFisher::StaticClass();
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}