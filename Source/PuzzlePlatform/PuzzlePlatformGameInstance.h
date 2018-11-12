// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UPuzzlePlatformGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
		// This is to get the game instance to work in a constructor mode
		UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer);

		// This is to get the game instance to work in a game instances
		virtual void Init();

		//This loads the first screen main menu seen on launch
		UFUNCTION(BlueprintCallable)
		void LoadMenu();

		// This gets the users to enter commands into the consolse while playing
		UFUNCTION(Exec)
		void Host();

		// This will print join to the screen 
		UFUNCTION(Exec)
		void Join(const FString& Address);

private:
		//Using the FClassFinder TSubClassOf for the UUser widget
		TSubclassOf<class UUserWidget>MenuClass;
};
