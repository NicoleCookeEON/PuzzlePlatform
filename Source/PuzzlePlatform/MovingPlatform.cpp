// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true; // This set/enables the ticking 

	SetMobility(EComponentMobility::Movable); // This get the object to move 
}

void AMovingPlatform::BeginPlay()// Begin Play
{
	Super::BeginPlay();

	if (HasAuthority()) // This is for the replication on the server and client
	{
		SetReplicates(true); // Set the replication of the objects on begin play 
		SetReplicateMovement(true); // Set the replication movement of the objects on begin play 
	}

	GlobalStartLocation = GetActorLocation(); // Gets the global location of the actor 
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation); // Gets the location and moves to a position	
}

void AMovingPlatform::Tick(float DeltaTime) // We want the object to move in a speed and direction 
{
	Super::Tick(DeltaTime); // This is to get the object to move 

	// This is to stop the platforms from moving when triggered and not supposed to be moving
	if (ActiveTriggers > 0)
	{
		if (HasAuthority()) // Server will replicate everything
		{
			FVector Location = GetActorLocation(); // We are getting the Actors Location 

			// these two floats are to get the box the move up and down in a certain direction 
			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size(); // This is to determine where the cube is to get it back 
			float JourneyTravelled = (Location - GlobalStartLocation).Size(); // This is to turn back 

			// this if statment is use the two floats to get the box the move up and down in a certain direction 
			if (JourneyTravelled > JourneyLength)
			{
				FVector Swap = GlobalStartLocation; // This is a holding varibale so it can be swapped later and not cause issues
				GlobalStartLocation = GlobalTargetLocation; // This is being overriden by the start location
				GlobalTargetLocation = Swap;
			}
			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal(); // Tager Locaiton is B - Place we are trying to get to. Location is A the starting point // GetSafeNormal wont modify anything  
			Location += Speed * DeltaTime * Direction; // We are getting the Actors Location, Direction and speed
			SetActorLocation(Location); // We are making sure the acors location has been set
		}
	}
}

// This increments (UPROPERTY(EditAnywhere) int ActiveTriggers = 1;)
// This is so we can activate the triggers
void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	// This makes so if the triggers are less than 0 then they will no longer be active anymore
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}
