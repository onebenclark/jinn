// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToMeanderPoint.h"
#include "Creature.h"
#include "CreatureAIController.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UMoveToMeanderPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACreatureAIController* aiController = Cast<ACreatureAIController>(OwnerComp.GetAIOwner());

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(aiController);
	if (navSystem)
	{
		FNavLocation location;
		navSystem->GetRandomPointInNavigableRadius(aiController->GetPawn()->GetActorLocation(), 150.0f, location);

		aiController->MoveToLocation(location.Location);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}