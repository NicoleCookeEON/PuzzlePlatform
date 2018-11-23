// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"

// This gets the button header
#include "Components/Button.h"


// This is going to be able to call the Cancel and Quit buttons 
bool UInGameMenu::Initialize()
{
	// Returning early if super failed to Initialize
	bool Success = Super::Initialize();
	if (!Success) return false;

	// The engine can return null, so this is put in to return null incase
	// Returning false so that if the null is false then we fail the Initialize
	if (!ensure(CancelButton != nullptr)) return false;

	// Cancel button being clicked event
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);

	// The engine can return null, so this is put in to return null incase
	// Returning false so that if the null is false then we fail the Initialize
	if (!ensure(QuitButton != nullptr)) return false;

	// Quit button being clicked event
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);

	return true;
}

// This is so we can call the teardown function 
void UInGameMenu::CancelPressed()
{
	Teardown();
}

// This is so we call the Game Instances to call a function that will allows us to travel to the MainMenu
void UInGameMenu::QuitPressed()
{
	// This allows us to call the MenuInterface, so we can call the LoadMainMenu to go back to the MainMenu
	if (MenuInterface != nullptr)
	{

	Teardown();

	MenuInterface->LoadMainMenu();

	}
}
