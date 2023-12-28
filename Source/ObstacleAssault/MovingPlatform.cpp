// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();

	// Logs in game
	//UE_LOG(LogTemp, Display, TEXT("===== Here is the Message ====== "));
	//UE_LOG(LogTemp, Display, TEXT("%f"), MoveDistance);

	// print string in logs
	//FString myString = "Gaurav is Great.. ";
	//FString myString = GetName();
	//UE_LOG(LogTemp, Display, TEXT("Print using Ftring : %s"), *myString);  OR
	//UE_LOG(LogTemp, Display, TEXT("Print using Ftring : %s"), *GetName());
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform :: MovePlatform(float DeltaTime)
{
	if(ShouldPlatformReturn())
	{
		FVector moveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation += moveDirection * MoveDistance;
		SetActorLocation(StartLocation);

		PlatformVelocity *= -1;
	}
	else
	{
		FVector currentLocation = GetActorLocation();
		currentLocation += PlatformVelocity * DeltaTime;
		SetActorLocation(currentLocation);
	}
}

void AMovingPlatform :: RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform :: ShouldPlatformReturn() const
{
	float DistanceMoved = FVector::Dist(StartLocation, GetActorLocation());
	return DistanceMoved > MoveDistance;
}

