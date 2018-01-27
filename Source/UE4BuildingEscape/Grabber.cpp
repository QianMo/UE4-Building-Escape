// Create by QianMo

#include "UE4BuildingEscape.h"
#include "Grabber.h"

#define  OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//log
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld( )->GetFirstPlayerController( )->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	//log
	//UE_LOG(LogTemp, Warning, TEXT("Location: %f ,Position : %s"),*PlayerViewPointLoacation.ToString(), *PlayerViewPointRotation.ToString( ));

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector( ) *Reach;

	//Draw a red trace in the world to visualise 
	DrawDebugLine(
		GetWorld( ),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.0f
	);

	// Ray-cast out to reach distance




	// See 
}

