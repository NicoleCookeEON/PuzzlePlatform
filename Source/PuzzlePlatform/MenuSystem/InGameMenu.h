// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	// This is going to be able to call the Cancel and Quit buttons 
	virtual bool Initialize();
	
private:
	// This binds the Cancel button in the WBP_InGameMenu
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	// This binds the Quit button in the WBP_InGameMenu
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	// This is so we can call the teardown function 
	UFUNCTION()
	void CancelPressed();

	// This is so we can call the teardown function 
	UFUNCTION()
	void QuitPressed();
	
};
