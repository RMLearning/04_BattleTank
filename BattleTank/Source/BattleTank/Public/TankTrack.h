// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TrackMaxDrivingForce = 400000; // assume 40t mass tank, 1g acceleration

	void ApplySidewaysForce();
	void DriveTrack(  );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UTankTrack();

	virtual void OnRegister() override;
	
	UFUNCTION()
	void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit );

	float CurrentThrottle = 0;
};
