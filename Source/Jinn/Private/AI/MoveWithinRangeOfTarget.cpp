// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveWithinRangeOfTarget.h"
#include "Creature.h"
#include "CreatureAIController.h"

EBTNodeResult::Type UMoveWithinRangeOfTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ACreatureAIController* aiController = Cast<ACreatureAIController>(OwnerComp.GetAIOwner());
	ACreature* creature = Cast<ACreature>(aiController->GetPawn());
	
	aiController->MoveToActor(creature->Target, creature->AttackRange-100);

	return EBTNodeResult::Succeeded;
}
