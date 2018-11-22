// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"

//Lets us get auto complete for the engine 
#include "Engine/Engine.h"

//Lets us use the FClassFinder ConstructorHelpers
#include "UObject/ConstructorHelpers.h"

//This allows us to use widgets in c++
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"

// This allows us to use the UUserWidget class
#include "MenuSystem/MainMenu.h"

// This allows us to use the UUserWidget class
#include "MenuSystem/MenuWidget.h"


UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	// This is to get the game instance to work in a constructor mode
	//UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));

	//This is the FClassFinder for trigegr platform to print out we have found it, then changed to UUserWidget
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));

	// The engine can return null, so this is put in to return null incase
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	//Save to my menu class to get hold of the T sub class object
	MenuClass = MenuBPClass.Class;

	//This is the FClassFinder for trigegr platform to print out we have found it, then changed to UUserWidget InGameMenu
	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));

	// The engine can return null, so this is put in to return null incase
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;

	//Save to my InGameMenu class to get hold of the T sub class object
	InGameMenuClass = InGameMenuBPClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
	// This is to get the game instance to work in a game instances
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

//This loads the first screen main menu seen on launch
void UPuzzlePlatformGameInstance::LoadMenu()
{
	// The engine can return null, so this is put in to return null incase
	if (!ensure(MenuClass != nullptr)) return;

	// This is creating the widget
	Menu = CreateWidget<UMainMenu>(this, MenuClass);

	// The engine can return null, so this is put in to return null incase
	if (!ensure(Menu != nullptr)) return;

	//Calling the MainMenu
	Menu->Setup();

	// This implements the MenuInterface to be able to use the inherited buttons
	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::InGameLoadMenu()
{
	// The engine can return null, so this is put in to return null incase
	if (!ensure(InGameMenuClass != nullptr)) return;

	// This is creats a UUserWidget to convert into a UMenuWidget
	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

	// The engine can return null, so this is put in to return null incase
	if (!ensure(Menu != nullptr)) return;

	//Calling the MainMenu
	Menu->Setup();

	// This implements the MenuInterface to be able to use the inherited buttons
	Menu->SetMenuInterface(this);
}

// This gets the users to enter commands into the consolse while playing
void UPuzzlePlatformGameInstance::Host()
{
	////Deactivates the cursor so the user can use the playercontroller
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

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
	////Deactivates the cursor so the user can use the playercontroller
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}
	
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
