// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

// This gets the button header
#include "Components/Button.h"

// This gets the WidgetSwitcher header
#include "Components/WidgetSwitcher.h"

// This gets the EditableTextBox header to use the IP adrress function
#include "Components/EditableTextBox.h"



// This is going to be able to call the host and join buttons
bool UMainMenu::Initialize()
{
	// Returning early if super failed to Initialize
	bool Success = Super::Initialize();
	if (!Success) return false;

	// The engine can return null, so this is put in to return null incase
	// Returning false so that if the null is false then we fail the Initialize
	if (!ensure(HostButton != nullptr)) return false;

	// Host button being clicked event
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	// The engine can return null, so this is put in to return null incase
	// Returning false so that if the null is false then we fail the Initialize
	if (!ensure(JoinButton != nullptr)) return false;

	// Join button being clicked event
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	// The engine can return null, so this is put in to return null incase
	// Returning false so that if the null is false then we fail the Initialize
	if (!ensure(CancelJoinMenuButton != nullptr)) return false;

	// CancelJoinMenuButton being clicked event
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	// The engine can return null, so this is put in to return null incase

	// Returning false so that if the null is false then we fail the Initialize
	if (!ensure(ConfirmJoinMenuButton != nullptr)) return false;

	// ConfirmJoinMenuButton being clicked event
	ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
}

void UMainMenu::HostServer()
{
	// Prints out host button being clicked event
	//UE_LOG(LogTemp, Warning, TEXT("I'm gonna host a server!"));

	if (MenuInterface != nullptr)
	{
		// Use this and call the host button
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	// This is to be able to enter text into the IPAddressFeild and this will be taken to the ConfirmJoinButton
	if (MenuInterface != nullptr)
	{
		// The engine can return null, so this is put in to return null incase
		if (!ensure(IPAddressFeild != nullptr)) return;

		const FString Address = IPAddressFeild->GetText().ToString();
		MenuInterface->Join(Address);
	}
}

void UMainMenu::OpenJoinMenu()
{
	// The engine can return null, so this is put in to return null incase
	if (!ensure(WidgetMenuSwitcher != nullptr)) return;

	// The engine can return null, so this is put in to return null incase
	if (!ensure(JoinMenu != nullptr)) return;

	//WidgetMenuSwitcher switch to another widget
	WidgetMenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	// The engine can return null, so this is put in to return null incase
	if (!ensure(WidgetMenuSwitcher != nullptr)) return;

	// The engine can return null, so this is put in to return null incase
	if (!ensure(JoinMenu != nullptr)) return;

	//WidgetMenuSwitcher switch to another widget
	WidgetMenuSwitcher->SetActiveWidget(MainMenu);
}




