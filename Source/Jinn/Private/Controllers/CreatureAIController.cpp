// Fill out your copyright notice in the Description page of Project Settings.

#include "CreatureAIController.h"
#include "Creature.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


ACreatureAIController::ACreatureAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	
	//static ConstructorHelpers::FObjectFinder<UBehaviorTree> treeAsset(TEXT("/Game/Blueprints/AI/CreatureBehaviorTree.CreatureBehaviorTree"));
	//BehaviorTree = treeAsset.Object;
	
	
}

void ACreatureAIController::BeginPlay()
{
	Super::BeginPlay();
	Pawn = Cast<ACreature>(GetPawn());
	BehaviorTree = Pawn->BehaviorTree;
	BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	//BehaviorTreeComponent->StartTree(*BehaviorTree);
	RunBehaviorTree(BehaviorTree);
}


void ACreatureAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	///*
	if (!BlackboardComponent->GetValueAsObject("CameraPawn"))
	{
		if (Pawn)
		{
			if (Pawn->Player)
			{
				BlackboardComponent->SetValueAsObject("CameraPawn", Pawn->Player);
			}
		}
	}
	if (!BlackboardComponent->GetValueAsObject("Target"))
	{
		if (Pawn)
		{
			if (Pawn->Target)
			{
				BlackboardComponent->SetValueAsObject("Target", Pawn->Target);
			}
		}
	}
	
}
