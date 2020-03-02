// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ExecuteQueuedAction.h"

#include "Creature.h"

void UAnimNotify_ExecuteQueuedAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACreature* Caller = Cast<ACreature>(MeshComp->GetOwner());
	if (!Caller || (Caller->ActionComponent->QueuedAction->Type == EActionType::Targeted && !Caller->Target)) return;
	Caller->ActionComponent->HandleQueuedAction();
}