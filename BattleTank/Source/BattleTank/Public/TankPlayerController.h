// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPosessedTankDeath();

protected:
	virtual void BeginPlay() override;

	virtual void SetPawn( APawn* InPawn ) override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompFef);

private:

	// Start the tank moving the barel so that a shot would
	// hit where the crosshair intersects with the world.
	void AimTowardsCrosshair();

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.333333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
};
