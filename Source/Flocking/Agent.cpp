// Fill out your copyright notice in the Description page of Project Settings.

#include "Flocking.h"
#include "Agent.h"


// Sets default values
AAgent::AAgent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
	
	
	gameMode = (AFlockingGameMode*)(GetWorld()->GetAuthGameMode());


	// Get the current location  
	position = GetActorLocation();
	velocity = GetActorForwardVector() * initVelocity;
	UE_LOG(Flocking, Log, TEXT("velocity  %s"), *(velocity.ToString()));
}

// Called every frame
void AAgent::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


	acceleration = Alignment().GetClampedToMaxSize(gameMode->maxAcceleration);
	velocity += acceleration * DeltaTime * 2000;
	velocity = velocity.GetClampedToMaxSize(gameMode->maxVelocity);
	position += velocity * DeltaTime;

	SetActorRelativeLocation(position, false);

	//UE_LOG(Flocking, Log, TEXT("velocity  %s"), *(acceleration.ToString()));
	if (velocity.Size() > 0)
	{
		SetActorRelativeRotation(FRotationMatrix::MakeFromX(velocity * DeltaTime).Rotator());
	}

}

FVector AAgent::Cohesion()
{
	FVector r(0);

	TArray<AAgent*> listNeighbor = gameMode->GetNeighborAgents(this);
	if (listNeighbor.Num() == 0)
	{
		return r;
	}

	for (AAgent* neighbor : listNeighbor)
	{
		r += neighbor->position;
	}
	r /= listNeighbor.Num();
	r -= this->position;

	r.Normalize();

	return r;
}

FVector AAgent::Separation()
{
	FVector r(0);

	TArray<AAgent*> listNeighbor = gameMode->GetNeighborAgents(this);
	if (listNeighbor.Num() == 0)
	{
		return r;
	}

	for (AAgent* neighbor : listNeighbor)
	{
		FVector toward = this->position - neighbor->position;
		float magnitude = toward.Size();
		if (magnitude > 0)
		{
			toward.Normalize();
			r += toward / magnitude;
		}
	}

	r.Normalize();

	return r;
}


FVector AAgent::Alignment()
{
	FVector r(0);

	TArray<AAgent*> listNeighbor = gameMode->GetNeighborAgents(this);
	if (listNeighbor.Num() == 0)
	{
		return r;
	}

	for (AAgent* neighbor : listNeighbor)
	{
		r += neighbor->velocity;
	}

	r.Normalize();

	return r;
}


FVector AAgent::Combine()
{
	return FVector();
}

