// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Your message"));

	// Find the owning Actor
	AActor* Owner = GetOwner( );

	// Create a rotator
	FRotator NewRotator = FRotator(0.0f, -60.0f, 0.0f);

	// Set the door rotation
	Owner->SetActorRotation(NewRotator);
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

