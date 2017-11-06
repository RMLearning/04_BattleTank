// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "TankAimingComponent.h"
#include "Tank.h"

#include "Engine/World.h"

/// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetPawn();
}

void ATankAIController::SetPawn( APawn * InPawn )
{
	Super::SetPawn( InPawn );

	if ( InPawn )
	{
		auto PossessedTank = Cast<ATank>( InPawn );
		if ( !ensure( PossessedTank ) ) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic( this, &ATankAIController::OnPossedTankDeath );
	}
}

void ATankAIController::OnPossedTankDeath()
{
	if ( !GetPawn() ) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if ( !PlayerTank )
	{
		UE_LOG( LogTemp, Warning, TEXT( "NoPlayer" ) )
		return;
	}
	if (!ensure(PlayerTank) && !ensure(ControlledTank)) { return; }

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	AimingComponent->AimAt( PlayerTank->GetActorLocation() );

	// if aim or locked 
	if ( AimingComponent->GetFiringState() == EFiringStatus::Locked )
	{
		AimingComponent->Fire(); // TODO: Limit Fire Rate
	}

}
