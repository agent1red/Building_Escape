// Copyright Kevin Hudson 2020.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("This is a warning!"));
	// UE_LOG(LogTemp, Error, TEXT("This is an error!"));
	// UE_LOG(LogTemp, Display, TEXT("Just a log"));

	FString ObjectName = GetOwner() -> GetName();
	FString ObjectPosition = GetOwner() ->GetActorLocation().ToString();
	FString ObjectRotation = GetOwner() ->GetActorTransform().GetRotation().ToString();
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

