// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"

// Generated is always last as it needs to be
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	// Setup
	void Setup();

	//Deactivates the cursor so the user can use the playercontroller
	void Teardown();

	// This gets the host button to now host when clicked
	void SetMenuInterface(IMenuInterface* MenuInterface);
	
//Everything that inherits from the UWidget has acces to it
protected:
	// This points to our MenuInterface
	IMenuInterface* MenuInterface;
	
};
