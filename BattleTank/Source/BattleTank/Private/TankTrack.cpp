// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic( this, &UTankTrack::OnHit );
}

void UTankTrack::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::OnHit( UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit )
{
	//GLog->Log( TEXT( "Track Hit" ) );
	//UE_LOG( LogTemp, Warning, TEXT( "Track Hit" ) )

	// Drive the tracks
	DriveTrack();

	// Apply sideways force
	ApplySidewaysForce();

	// Reset Throttle
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate the slippage speed
	auto SlippageSpeed = FVector::DotProduct( GetRightVector(), GetComponentVelocity() );
	// Work-out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// Calculate and apply sideways force (F = M * A)
	auto TankRoot = Cast<UStaticMeshComponent>( GetOwner()->GetRootComponent() );
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce( CorrectionForce );
}

void UTankTrack::DriveTrack(  )
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::SetThrottle(float Throttle)
{	
	CurrentThrottle = FMath::Clamp<float>( CurrentThrottle + Throttle, -1, 1 );
}

