// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void SetPawn( APawn* InPawn ) override;

	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	float AcceptanceRadius = 3000.0f;

private:
	UFUNCTION()
	void OnPossedTankDeath();

};
