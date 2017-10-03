// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = Cast<ATank>(GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		// TODO: Move towards the player

		// Aim towards the player
		Cast<ATank>(GetPawn())->AimAt(PlayerTank->GetActorLocation());

		Cast<ATank>(GetPawn())->Fire(); // TODO: Limit Fire Rate
	}
}
