// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "FlockingGameMode.h"
//#include "FlockingController.h"


#include "GameFramework/Actor.h"
#include "Agent.generated.h"


//class AFlockingGameMode;


UCLASS()
class FLOCKING_API AAgent : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAgent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Flocking)
	float initVelocity = 1000;

	UPROPERTY(EditAnywhere, Category = Flocking)
	FVector position;

	UPROPERTY(EditAnywhere, Category = Flocking)
	FVector rotation;

	UPROPERTY(EditAnywhere, Category = Flocking)
	FVector velocity;

	UPROPERTY(EditAnywhere, Category = Flocking)
	FVector acceleration;

	AFlockingGameMode* gameMode;

	FVector wanderTarget = FVector(0.0f);


	FVector Cohesion();

	FVector Separation();

	FVector Alignment();

	FVector Combine();

	void WrapAroundPosition(FVector& pos);

	float WrapAround(float value, float min, float max);
	
	bool IsInView(const AAgent* otherAgent);

	FVector Wander(float DeltaTime);

	float RandomBinomial();
	

};
