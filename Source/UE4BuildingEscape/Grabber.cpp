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

	// Find attached phyics handle
	FindPhysicsHandleComponent( );

	// Setup (assumed) attached input component
	SetupInputComponent( );
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle)
	{
		return;
	}

	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we are holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}


}




#pragma region 初始化部分


// Find attached phyics handle
void UGrabber::FindPhysicsHandleComponent( )
{
	// Look for attached Physics Handle
	PhysicsHandle = GetOwner( )->FindComponentByClass<UPhysicsHandleComponent>( );
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component "), *GetOwner( )->GetName( ));
	}

}


// Setup (assumed) attached input component
void UGrabber::SetupInputComponent( )
{
	// Look for attached Physics Handle
	InputComponent = GetOwner( )->FindComponentByClass<UInputComponent>( );
	if (InputComponent)
	{
		// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		//log
		UE_LOG(LogTemp, Error, TEXT("%s missing input handle component "), *GetOwner( )->GetName( ));
	}
}

#pragma endregion



void UGrabber::Grab( )
{

	// LINE TRACE and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach( );
	auto ComponentToGrab = HitResult.GetComponent( );
	auto ActorHit = HitResult.GetActor( );

	// If we hit something then attach a physics handle
	if (ActorHit)
	{
		// attach physics handle
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None, //no bons needed
			ComponentToGrab->GetOwner( )->GetActorLocation( ),
			true //allow rotation
			);
	}
}

void UGrabber::Release( )
{
	if (!PhysicsHandle)
	{
		return;
	}
	PhysicsHandle->ReleaseComponent( );
}



// Return hit for first physics body in reach
const FHitResult UGrabber::GetFirstPhysicsBodyInReach( )
{


	// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner( ));

	// Line-trace (AKA ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld( )->LineTraceSingleByObjectType(
		OUT Hit,
		GetReachLineStart( ),
		GetReachLineEnd( ),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	//UE_LOG(LogTemp, Warning, TEXT(" here!"));

	// See what we hit
	AActor* ActorHit = Hit.GetActor( );
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit : %s"), *(ActorHit->GetName( )));
	}


	return Hit;
}

// Return current end of reach line
FVector UGrabber::GetReachLineStart( )
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld( )->GetFirstPlayerController( )->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}



// Return current end of reach line
FVector UGrabber::GetReachLineEnd( )
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld( )->GetFirstPlayerController( )->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector( ) *Reach;
}

