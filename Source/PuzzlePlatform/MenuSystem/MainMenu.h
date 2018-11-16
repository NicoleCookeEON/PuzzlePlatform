// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
// Generated is always last as it needs to be
#include "MainMenu.generated.h"



/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	// This gets the host button to now host when clicked
	void SetMenuInterface(IMenuInterface* MenuInterface);

	// Setup
	void Setup();

	//Deactivates the cursor so the user can use the playercontroller
	void Teardown();
	
protected:
	// This is going to be able to call the host and join buttons 
	virtual bool Initialize();

private:
	// This binds the host button in the WBP_MainMenu
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	// This binds the join button in the WBP_MainMenu
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	// This binds the CancelJoinMenu button in the WBP_MainMenu
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelJoinMenuButton;
	
	// This binds the ConfirmJoinMenuButton button in the WBP_MainMenu
	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmJoinMenuButton;
	
	// This binds the WidgetSwitcher in the WBP_MainMenu
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WidgetMenuSwitcher;

	// This binds the MainMenu button in the WBP_MainMenu
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	// This binds the JoinMenu button in the WBP_MainMenu
	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	// This binds the EditableText Box for the IPAddressFeild to be usable in the WBP_MainMenu
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAddressFeild;

	// This binds the HostButton in the WBP_MainMenu
	UFUNCTION()
	void HostServer();
	
	// This binds the JoinButton in the WBP_MainMenu
	UFUNCTION()
	void JoinServer();

	// This binds the OpenJoinMenu in the WBP_MainMenu
	UFUNCTION()
	void OpenJoinMenu();

	// This binds the OpenMainMenu in the WBP_MainMenu
	UFUNCTION()
	void OpenMainMenu();

	// This points to our MenuInterface
	IMenuInterface* MenuInterface;
};
