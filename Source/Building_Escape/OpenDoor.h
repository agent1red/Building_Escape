// Copyright Kevin Hudson 2020.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;

public:	
	// Sets default values for this component's properties
	UOpenDoor();
private:
// private declarations 
float InitialYaw;
float CurrentYaw;	

UPROPERTY(EditAnywhere)// expose this property in the editor 
float OpenAngle = 90.F;

UPROPERTY(EditAnywhere)
ATriggerVolume* PressurePlate;

UPROPERTY(EditAnywhere)
AActor* ActorThatOpens;

float DoorLastOpened = 0.f;

UPROPERTY(EditAnywhere)
float DoorCloseDelay = 2.f;

UPROPERTY(EditAnywhere)
float DoorOpenSpeed = 2.f;

UPROPERTY(EditAnywhere)
float MassToOpenDoors = 50.f;

UPROPERTY(EditAnywhere)
float DoorClosedSpeed = 2.f;

float CurrentTime = 0.f;
	
};
