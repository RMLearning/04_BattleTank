// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurrent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))//, hidecategories = ("Collision"))
class BATTLETANK_API UTankTurrent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max counter-clockwise movement speed, and +1 is max clockwise movement speed
	void Rotate(float RelativeSpeed);

	UPROPERTY(EditAnywhere, Category="Setup")
	float MaxDegreesPerSecond = 5.0f;
};
