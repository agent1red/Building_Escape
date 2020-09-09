// Copyright Kevin Hudson 2020.
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

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
	if (PhysicsHandle)
	{
		//Physics not found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s!"), 
			*GetOwner() -> GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber pressed"));

	// TODO to only aycast when key is pressed.
	GetFirstPhysicsBodyInReach();
	//If we hit something then attach the phisics handle.
	// TODO attach physics handle. 
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber released"));
	// TODO remove/release the physics handle.
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		// if the physics handle is attached.
		// move the object we are holding. 

		
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Get the players viewpoint 

		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;

	GetWorld() ->GetFirstPlayerController() ->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);


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
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	FHitResult Hit; 
	// Ray-cast out to a certain distance (reach) private member variable 
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());


	GetWorld() ->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// See what it hits (is that something we can pick up?) 
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor hits: %s"), *(ActorHit ->GetName()));
	}
	return Hit;
}
