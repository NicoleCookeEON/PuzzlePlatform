// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

// This gets the button header
#include "Components/Button.h"

// This gets the WidgetSwitcher header
#include "Components/WidgetSwitcher.h"



// This is going to be able to call the host and join buttons
bool UMainMenu::Initialize()
{
	// Call the super Initialize
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

	return true;
}

// This gets the host button to now host when clicked
void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::Setup()
{
	//This adds the widget to the viewport
	this->AddToViewport();

	//check the world is not null
	UWorld* World = GetWorld();

	// The engine can return null, so this is put in to return null incase
	if (!ensure(World != nullptr)) return;

	//Client connecting to a server using an IP address in the command line in the editor 
	APlayerController* PlayerController = World->GetFirstPlayerController();

	// The engine can return null, so this is put in to return null incase
	if (!ensure(PlayerController != nullptr)) return;

	//This creates the input through a struct 
	FInputModeUIOnly InputModeData;

	//This converts the bwidget and converts into a swidget
	InputModeData.SetWidgetToFocus(this->TakeWidget());

	//This locks the mouse on to the screen onto the viewport
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	//This takes the playercontroller to set the inputdata on the screen 
	PlayerController->SetInputMode(InputModeData);

	// This shows the cursor
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::Teardown()
{
	//This removes the widget from the viewport
	this->RemoveFromViewport();

	//check the world is not null
	UWorld* World = GetWorld();

	// The engine can return null, so this is put in to return null incase
	if (!ensure(World != nullptr)) return;

	//Client connecting to a server using an IP address in the command line in the editor 
	APlayerController* PlayerController = World->GetFirstPlayerController();

	// The engine can return null, so this is put in to return null incase
	if (!ensure(PlayerController != nullptr)) return;
	
	//This creates the input through a struct
	FInputModeGameOnly InputModeData;

	//This takes the playercontroller to set the inputdata on the screen 
	PlayerController->SetInputMode(InputModeData);

	// This shows the cursor
	PlayerController->bShowMouseCursor = false;
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




