// Fill out your copyright notice in the Description page of Project Settings.

#include "Flocking.h"
#include "FlockingGameMode.h"


#include "Agent.h"

void AFlockingGameMode::InitGameState()
{
	Super::InitGameState();



	for (int i = 0; i < agentCount; i++)
	{
		FVector randomPos(FMath::RandRange(-mapSize.X, mapSize.X), FMath::RandRange(-mapSize.Y, mapSize.Y), 0);
		FRotator randRotator(0, FMath::RandRange(0, 360), 0);
		listAgent.Add((AAgent*)GetWorld()->SpawnActor(agent_BP, &randomPos, &randRotator));
	}
	
	
}

TArray<AAgent*> AFlockingGameMode::GetNeighborAgents(const AAgent* agent)
{
	TArray<AAgent*> list;
	for (AAgent* otherAgent : listAgent)
	{
		if (otherAgent == agent)
		{
			continue;
		}

		if (FVector::Dist(otherAgent->position, agent->position) <= radiusCohesion)
		{
			list.Add(otherAgent);
		}
	}

	return list;
}
