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
	
}

// Called every frame
void AAgent::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


	acceleration = Combine().GetClampedToMaxSize(gameMode->maxAcceleration);
	velocity += acceleration * DeltaTime;
	velocity = velocity.GetClampedToMaxSize(gameMode->maxVelocity);
	position += velocity * DeltaTime;

	WrapAroundPosition(position);

	SetActorRelativeLocation(position, false);

	//UE_LOG(Flocking, Log, TEXT("velocity  %s"), *(acceleration.ToString()));
	if (velocity.Size() > 0)
	{
		SetActorRelativeRotation(FRotationMatrix::MakeFromX(velocity).Rotator());
	}

}

FVector AAgent::Cohesion()
{
	FVector r(0.0f);

	TArray<AAgent*> listNeighbor = gameMode->GetNeighborAgents(this, gameMode->radiusCohesion);
	if (listNeighbor.Num() == 0)
	{
		return r;
	}

	int count = 0;
	for (AAgent* neighbor : listNeighbor)
	{
		if (IsInView(neighbor))
		{
			r += neighbor->position;
			++count;
		}
	}
	if (count == 0)
	{
		return r;
	}

	r /= count;
	r -= this->position;

	r.Normalize();

	return r;
}

FVector AAgent::Separation()
{
	FVector r(0.0f);

	TArray<AAgent*> listNeighbor = gameMode->GetNeighborAgents(this, gameMode->radiusSeparation);
	if (listNeighbor.Num() == 0)
	{
		return r;
	}

	for (AAgent* neighbor : listNeighbor)
	{
		if (IsInView(neighbor))
		{
			FVector toward = this->position - neighbor->position;
			float magnitude = toward.Size();
			if (magnitude > 0)
			{
				toward.Normalize();
				r += toward / magnitude;
			}
		}
	}

	r.Normalize();

	return r;
}


FVector AAgent::Alignment()
{
	FVector r(0.0f);

	TArray<AAgent*> listNeighbor = gameMode->GetNeighborAgents(this, gameMode->radiusAlignment);
	if (listNeighbor.Num() == 0)
	{
		return r;
	}

	for (AAgent* neighbor : listNeighbor)
	{
		if (IsInView(neighbor))
		{
			r += neighbor->velocity;
		}
	}

	r.Normalize();

	return r;
}


FVector AAgent::Combine()
{
	return Cohesion() * gameMode->kCohesion + Separation() * gameMode->kSeparation + Alignment() * gameMode->kAlignment;
}

void AAgent::WrapAroundPosition(FVector& pos)
{
	FVector2D mapSize = gameMode->mapSize;
	pos.X = WrapAround(pos.X, -mapSize.X, mapSize.X);
	pos.Y = WrapAround(pos.Y, -mapSize.Y, mapSize.Y);
}

float AAgent::WrapAround(float value, float min, float max)
{
	if (value > max)
	{
		value = min;
	}
	else if (value < min)
	{
		value = max;
	}

	return value;
}

bool AAgent::IsInView(const AAgent* otherAgent)
{
	if (gameMode->enableAgentViewAngle == false)
	{
		return true;
	}

	FVector tmp = (otherAgent->position - this->position);
	tmp.Normalize();
	float angle = acosf(FVector::DotProduct(tmp, GetActorForwardVector()));
	return (angle >= gameMode->agentViewAngle.X && angle <= gameMode->agentViewAngle.Y);
}
/*
FVector AAgent::Wander(float DeltaTime)
{
	float jitter = gameMode->agnetJitter * DeltaTime;
	wanderTarget += FVector(RandomBinomial() * jitter, RandomBinomial() * jitter, 0);
	wanderTarget.Normalize();
	wanderTarget *= gameMode->agnetWanderRadius;

	FVector localTarget = wanderTarget + FVector(gameMode->agnetWanderDistance, 0, 0);

	return FVector();
}

float AAgent::RandomBinomial()
{
	return FMath::FRandRange(0.0f, 1.0f) - FMath::FRandRange(0.0f, 1.0f);
}
*/
