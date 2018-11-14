// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

// This gets the button header
#include "Components/Button.h"


// This is going to be able to call the host and join buttons
bool UMainMenu::Initialize()
{
	// Call the super Initialize
	bool Success = Super::Initialize();
	if (!Success) return false;

	// The engine can return null, so this is put in to return null incase
	// Returning false so that if the null is false then we fail the Initialize
	if (!ensure(Host != nullptr)) return false;

	// Host button being clicked event
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	return true;

}

void UMainMenu::HostServer()
{
	// Prints out host button being clicked event
	UE_LOG(LogTemp, Warning, TEXT("I'm gonna host a server!"));
}




