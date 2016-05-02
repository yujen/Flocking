// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "GameFramework/GameMode.h"
#include "FlockingGameMode.generated.h"


class AAgent;


/**
 * 
 */
UCLASS()
class FLOCKING_API AFlockingGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:


	virtual void InitGameState() override;


	TArray<AAgent*> GetNeighborAgents(const AAgent* agent);
	


	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	int32 agentCount = 10;


	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float maxVelocity = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float maxAcceleration = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float radiusCohesion = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float radiusSeparation = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float radiusAlignment = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float Kc = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float Ks = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float Ka = 0;
	

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	TSubclassOf<class AAgent> agent_BP;

	
	TArray<AAgent*> listAgent;

};
