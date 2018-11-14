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

protected:
	// This is going to be able to call the host and join buttons 
	virtual bool Initialize();

private:
	// This binds the host button in the WBP_MainMenu
	UPROPERTY(meta = (BindWidget))
	class UButton* Host;

	// This binds the join button in the WBP_MainMenu
	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	UFUNCTION()
	void HostServer();

	// This points to our MenuInterface
	IMenuInterface* MenuInterface;
};
