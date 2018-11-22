// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"


void UMenuWidget::Setup()
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

void UMenuWidget::Teardown()
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

// This gets the host button to now host when clicked
void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

