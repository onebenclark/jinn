// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffect.h"
#include "Creature.h"

UStatusEffect::UStatusEffect()
{
	Time = 0.0f;
}

void UStatusEffect::Effects(ACreature* AffectedCreature)
{
	BPEffects(AffectedCreature);
}