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

	//UPROPERTY(VisibleAnywhere, Category = Flocking)
	AFlockingGameMode* gameMode;


	FVector Cohesion();

	FVector Separation();

	FVector Alignment();

	FVector Combine();

};
