// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"
#include "Creature.h"

UAction::UAction()
{
	Range = 0.0f;
	Cooldown = 0.0f;
	CooldownRate = 0.01f;
	Cost = 0.0f;
	Type = EActionType::Targeted;
}

AActor* UAction::Spawn(FVector location, FRotator rotation)
{
	FActorSpawnParameters params;
	UWorld* world = GetWorld();
	if (!world) return NULL;
	return world->SpawnActor(SpawnedClass, &location, &rotation, params);
}

bool UAction::Execute(ACreature* Caller, ACreature* Target)
{
	if (!Target || !Caller || Caller->StatsComponent->Will >= Caller->StatsComponent->MaxWill) return true;
	FVector direction = (Target->GetActorLocation() - Caller->GetActorLocation()).GetSafeNormal2D();
	
	Caller->SetActorRotation(direction.ToOrientationRotator());
	Cooldown = 1.0f;
	Caller->StatsComponent->Will += Cost;
	//Call blueprint implement ActionEffects method.
	if(Anim == EActionAnim::None) return ActionEffects(Caller, Target);
	Caller->ActionComponent->ActionAnim = Anim;
	Caller->ActionComponent->QueuedAction = this;
	CallingCreature = Caller;
	TargetedCreature = Target;
	return true;
}

bool UAction::Effects()
{
	bool success = ActionEffects(CallingCreature, TargetedCreature);

	CallingCreature = 0;
	TargetedCreature = 0;
	 
	return success;
}