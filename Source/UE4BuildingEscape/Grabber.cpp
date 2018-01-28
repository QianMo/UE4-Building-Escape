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
	
	// Look for attached Physics Handle
	PhysicsHandle = GetOwner( )->FindComponentByClass<UPhysicsHandleComponent>( );
	if (PhysicsHandle)
	{
		// Physics handle is found
	}
	else
	{
		//log
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component "), *GetOwner()->GetName());
	}

	// Look for attached Physics Handle
	InputComponent = GetOwner( )->FindComponentByClass<UInputComponent>( );
	if (InputComponent)
	{
		// Input handle is found
		UE_LOG(LogTemp, Warning, TEXT("Input handle is found "));

		// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);

	}
	else
	{
		//log
		UE_LOG(LogTemp, Error, TEXT("%s missing input handle component "), *GetOwner( )->GetName( ));
	}

	



}


void UGrabber::Grab( )
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed!"));
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

	// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner( ));

	// Line-trace (AKA ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld( )->LineTraceSingleByObjectType( 
	    OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd ,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	//UE_LOG(LogTemp, Warning, TEXT(" here!"));

	// See what we hit
	AActor* ActorHit = Hit.GetActor( );
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit : %s"), *(ActorHit->GetName()));
	}
	// Ray-cast out to reach distance




	// See 
}

