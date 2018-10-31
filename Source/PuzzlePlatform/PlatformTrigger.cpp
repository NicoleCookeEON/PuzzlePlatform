// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformTrigger.h"

// This was needed to be added to activate the UBoxComponent
#include "Components/BoxComponent.h" 

//This is the to get auto complete on the for loop in OnOverlapBegin
#include "MovingPlatform.h"


// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating a default sub object to make the private trigger variable work
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));

	//Ensure that trigger volume is not equal to null pointer
	if(!ensure(TriggerVolume != nullptr)) return;
	
	// Collision primitive that defines the transform (location, rotation, scale) of this Actor.
	RootComponent = TriggerVolume;

	//This is for the box to be triggerd when being passed into 
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// This is the signature (docs.unrealengine.com/en-us/Gameplay/ClassCreation/CodeOnly)
void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//This is text sending out to the log no know we have hit the trigger of the box
	//UE_LOG(LogTemp, Warning, TEXT("Deactivated"));

	//This is to read the Tarry
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
	}
} 

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//This is text sending out to the log no know we have hit the trigger of the box
	//UE_LOG(LogTemp, Warning, TEXT("Deactivated"));

	//This is to read the Tarry
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
}
