// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Creature.h"

UItem::UItem()
{
	Type = EItemType::Consumable;
	
}

bool UItem::Use(ACreature* Target)
{

	return Effects(Target);
}

