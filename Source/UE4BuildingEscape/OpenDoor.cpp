// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4BuildingEscape.h"
#include "OpenDoor.h"

#define  OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay( )
{
	Super::BeginPlay( );

	//UE_LOG(LogTemp, Warning, TEXT("Your message"));

	// Find the owning Actor
	Owner = GetOwner( );
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (GetTotalMassOfActorsOnPlate( ) > 30.0f) // TODO make into a parameter
	{
		OpenDoor( );
		LastDoorOpenTime = GetWorld( )->GetTimeSeconds( );
	}

	// Check if it'is time to close the door
	if (GetWorld( )->GetTimeSeconds( ) - LastDoorOpenTime > DoorClosrDelay)
	{
		CloseDoor( );
	}
}

void UOpenDoor::OpenDoor( )
{
	// Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor( )
{
	// Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

float UOpenDoor::GetTotalMassOfActorsOnPlate( )
{
	float TotalMass = 0.f;

	//Find all the overlaping actors
	TArray<AActor*> OverlappingActors;

	if (PressurePlate==nullptr)
	{
		return 0.f;
	}

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//Iterate through them adding their masses
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>( )->GetMass( );
		//UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName( ));
	}

	return TotalMass;
}

