// Copyright Kevin Hudson 2020.
#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner() ->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent ->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent ->BindAction("Release",IE_Released, this, &UGrabber::Release);
	}	
}
//Checking for Physics Handle Component
void UGrabber::FindPhysicsHandle()
{
	
	PhysicsHandle = GetOwner() ->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s!"), 
			*GetOwner() -> GetName());
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	//If we hit something then attach the phisics handle.
	if (HitResult.GetActor())
	{
		PhysicsHandle -> GrabComponentAtLocation
			(
				ComponentToGrab,
				NAME_None,
				GetPlayersReach()
			);
	}
}


void UGrabber::Release()
{
	PhysicsHandle -> ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		// if the physics handle is attached.
		if (PhysicsHandle -> GrabbedComponent)
		{
			// move the object we are holding. 
			PhysicsHandle -> SetTargetLocation(GetPlayersReach());
		}		
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	
	FHitResult Hit; 
	// Ray-cast out to a certain distance (reach) private member variable 
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld() ->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersWorldPos(),
		GetPlayersReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}

FVector UGrabber::GetPlayersReach() const
{
	FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;

	GetWorld() ->GetFirstPlayerController() ->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::GetPlayersWorldPos() const
{
	// Get the players viewpoint 
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;

	GetWorld() ->GetFirstPlayerController() ->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

	// UE_LOG(LogTemp, Warning, TEXT("Location:%s  Rotation: %s"), 
	// 	*PlayerViewPointLocation.ToString(), 
	// 	*PlayerViewPointRotation.ToString()
	// );

	
	/* Draw a line from player showing the reach - Example code
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	 );*/
