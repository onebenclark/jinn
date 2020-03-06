// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine.h"

#include "CameraPawn.h"
#include "CreatureAIController.generated.h"

/**
 * 
 */
UCLASS()
class JINN_API ACreatureAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACreatureAIController();

protected:
	void BeginPlay() override;

	//void OnPossess(APawn* InPawn) override;

	ACreature* Pawn;
public:
	void Tick(float DeltaTime) override;

	class UBlackboardComponent* BlackboardComponent;

	class UBehaviorTreeComponent* BehaviorTreeComponent;

	class UBehaviorTree* BehaviorTree;


};
