// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	ActionAnim = EActionAnim::None;
	AvailableAbilityPoints = 0;
	LifePoints = 0;
	MindPoints = 0;
	ElementalPoints = 0;
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (LeftFaceButtonAction) ActionMap.Add(LeftFaceButtonAction, NewObject<UAction>(this, LeftFaceButtonAction.Get()));
	if (RightFaceButtonAction) ActionMap.Add(RightFaceButtonAction, NewObject<UAction>(this, RightFaceButtonAction.Get()));
	if (TopFaceButtonAction) ActionMap.Add(TopFaceButtonAction, NewObject<UAction>(this, TopFaceButtonAction.Get()));
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	for (const TPair<TSubclassOf<class UAction>, UAction*>& action : ActionMap)
	{
		if (!action.Value) continue;
		if (action.Value->Cooldown > 0.0f) action.Value->Cooldown -= action.Value->CooldownRate;
		if (action.Value->Cooldown < 0.0f) action.Value->Cooldown = 0;
	}
}

void UActionComponent::DecrementActionCooldowns(float DeltaTime)
{
}

void UActionComponent::AddAvailableAction(TSubclassOf<class UAction> ActionClass)
{
	ActionMap.Add(ActionClass, NULL);
}

void UActionComponent::ExecuteAction(TSubclassOf<class UAction> ActionClass, ACreature* Caller, AActor* Target)
{
	if (!ActionMap[ActionClass]) ActionMap.Add(ActionClass, NewObject<UAction>(this, ActionClass.Get()));
	if (ActionMap[ActionClass]->Cooldown > 0.0f) return;
	ActionMap[ActionClass]->Execute(Caller, Target);
}

void UActionComponent::ExecuteLeftFaceButtonAction(ACreature* Caller, AActor* Target)
{
	if (!LeftFaceButtonAction)
	{
		return;
	}
	if (!ActionMap[LeftFaceButtonAction]) ActionMap.Add(LeftFaceButtonAction, NewObject<UAction>(this, LeftFaceButtonAction.Get()));
	if (ActionMap[LeftFaceButtonAction]->Cooldown > 0.0f) return;
	ActionMap[LeftFaceButtonAction]->Execute(Caller, Target);
}

void UActionComponent::ExecuteRightFaceButtonAction(ACreature* Caller, AActor* Target)
{
	if (!RightFaceButtonAction)
	{
		return;
	}
	if (!ActionMap[RightFaceButtonAction]) ActionMap.Add(RightFaceButtonAction, NewObject<UAction>(this, RightFaceButtonAction.Get()));
	if (ActionMap[RightFaceButtonAction]->Cooldown > 0.0f) return;
	ActionMap[RightFaceButtonAction]->Execute(Caller, Target);
}

void UActionComponent::ExecuteTopFaceButtonAction(ACreature* Caller, AActor* Target)
{
	if (!TopFaceButtonAction)
	{
		return;
	}
	if (!ActionMap[TopFaceButtonAction]) ActionMap.Add(TopFaceButtonAction, NewObject<UAction>(this, TopFaceButtonAction.Get()));
	if (ActionMap[TopFaceButtonAction]->Cooldown > 0.0f) return;
	ActionMap[TopFaceButtonAction]->Execute(Caller, Target);
}

void UActionComponent::ExecuteAttackAction(ACreature* Caller, AActor* Target)
{
	if (!AttackAction)
	{
		return;
	}
	if (!ActionMap[AttackAction]) ActionMap.Add(AttackAction, NewObject<UAction>(this, AttackAction.Get()));
	if (ActionMap[AttackAction]->Cooldown > 0.0f)
	{
		return;
	}
	ActionMap[AttackAction]->Execute(Caller, Target);
}

void UActionComponent::ChangeAttackAction(TSubclassOf<class UAction> NewAttackAction)
{
	ActionMap.Remove(AttackAction);
	AttackAction = NewAttackAction;
}

void UActionComponent::HandleQueuedAction()
{
	if (!QueuedAction) return;
	QueuedAction->Effects();
	
	if(QueuedAction->IsComplete())QueuedAction = 0;
}

