// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
	//This is the object we want to move 
	public:
		AMovingPlatform();

		virtual void BeginPlay() override;// Begin Play

		virtual void Tick(float DeltaTime) override; // This is the speed we want the object to move in 

		UPROPERTY(EditAnywhere) // This is how fast we want the object to move 
		float Speed = 20;

		// This is to show the target location to the public (such as designers)
		UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))  // The Meta = (MakeEditWidget = true) shows the target on screen
		FVector TargetLocation;

		//Be able to activate the tirggers when needed
		void AddActiveTrigger();
		void RemoveActiveTrigger();

private:
	FVector GlobalTargetLocation; //Gets the global target 
	FVector GlobalStartLocation; //Gets the global start location 

	//Stores the activated triggers.
	//User can change in the editor
	UPROPERTY(EditAnywhere)
		int ActiveTriggers = 1;
};
