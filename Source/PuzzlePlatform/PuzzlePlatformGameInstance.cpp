// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"

//Lets us get auto complete for the engine 
#include "Engine/Engine.h"



UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	// This is to get the game instance to work in a constructor mode
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UPuzzlePlatformGameInstance::Init()
{
	// This is to get the game instance to work in a game instances
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

// This gets the users to enter commands into the consolse while playing
void UPuzzlePlatformGameInstance::Host()
{
	// Log this out to the screen not to the console, lets the user see things on the screen 
	UEngine* Engine = GetEngine();

	// The engine can return null, so this is put in to return null incase
	if (!ensure(Engine != nullptr)) return;

	//This replaces the last message on the on screen message and leave on screen for 2 seconds, use a display color of green, takes the Fsting so we can print what we like  
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	//Map travelling - Type of the world 
	UWorld* World = GetWorld();

	// The engine can return null, so this is put in to return null incase
	if (!ensure(World != nullptr)) return;

	//When entering Host into the comman line the user will be sent from the lobby map to the ThirdPersonExampleMap
	//If listen isn't added to the end of the URL other user won't be able to travel to the same map as they won't be able to see the server hosting
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	// Log this out to the screen not to the console, lets the user see things on the screen 
	UEngine* Engine = GetEngine();

	// The engine can return null, so this is put in to return null incase
	if (!ensure(Engine != nullptr)) return;

	// This replaces the last message on the on screen message and leave on screen for 2 seconds, use a display color of green, takes the Fsting so we can print what we like  
	// Formatting an adrress into the string is %s
	// FString::Print allows us to format the argument
	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	//Client connecting to a server using an IP address in the command line in the editor 
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	// The engine can return null, so this is put in to return null incase
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
