// Copyright Kevin Hudson 2020.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner() -> GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw; 

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the door component on i, but no pressureplate set!"), *GetOwner() ->GetName());
	}
	ActorThatOpens = GetWorld() ->GetFirstPlayerController() ->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	CurrentTime = GetWorld() ->GetTimeSeconds();
	if (PressurePlate && PressurePlate -> IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld() ->GetTimeSeconds();
		return;
	}
	
	// if the door has been opened longer than DoorCloseDelay
	if (!PressurePlate -> IsOverlappingActor(ActorThatOpens) && CurrentTime - DoorLastOpened > DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
		return;
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner() -> GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("The Yaw is: %f"), GetOwner() -> GetActorRotation().Yaw);
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);
	FRotator DoorRotation = GetOwner() ->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner() -> SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorClosedSpeed);
	FRotator DoorRotation = GetOwner() ->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner() -> SetActorRotation(DoorRotation);
}

