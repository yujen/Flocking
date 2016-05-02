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
	FVector2D mapSize;



	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float maxVelocity = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float maxAcceleration = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	FVector2D agentViewAngle;

	//UPROPERTY(EditAnywhere, Category = FlockingConfig)
	//float agnetJitter = 0;

	//UPROPERTY(EditAnywhere, Category = FlockingConfig)
	//float agnetWanderRadius = 0;

	//UPROPERTY(EditAnywhere, Category = FlockingConfig)
	//float agnetWanderDistance = 0;



	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float radiusCohesion = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float radiusSeparation = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float radiusAlignment = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float kCohesion = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float kSeparation = 0;

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	float kAlignment = 0;
	

	UPROPERTY(EditAnywhere, Category = FlockingConfig)
	TSubclassOf<class AAgent> agent_BP;

	
	TArray<AAgent*> listAgent;

};
