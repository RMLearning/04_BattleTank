// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{

	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(RawNewElevation, MinDegreeElevation, MaxDegreeElevation);

	UE_LOG(LogTemp, Warning, TEXT("Move Rotation %f"), RawNewElevation)
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}

