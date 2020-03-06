// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_DoDamage.h"

#include "Creature.h"

void UAnimNotify_DoDamage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACreature* Caller = Cast<ACreature>(MeshComp->GetOwner());
	if (!Caller || !Caller->Target) return;
	Caller->ActionComponent->ExecuteAttackAction(Caller, Caller->Target);
}