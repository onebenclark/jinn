// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotionItem.h"
#include "Creature.h"

UHealthPotionItem::UHealthPotionItem()
{
	Type = EItemType::Consumable;
}

bool UHealthPotionItem::Use(ACreature* Target)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, L"Health Potion Use");
	if ((Target->StatsComponent->Health + 15.0f) > Target->StatsComponent->MaxHealth)
	{
		Target->StatsComponent->Health = Target->StatsComponent->MaxHealth;
	}
	else
	{
		Target->StatsComponent->Health += 15.0f;
	}

	return true;
}
