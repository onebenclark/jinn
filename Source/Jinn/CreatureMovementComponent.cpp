// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureMovementComponent.h"
#include "ActionPlacementActor.h"
#include "Engine.h"

void UCreatureMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	MaxSpeed = 400.0f;
}

void UCreatureMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	FVector movement = ConsumeInputVector();
	FHitResult hit;
	SafeMoveUpdatedComponent(movement, UpdatedComponent->GetComponentQuat(), true, hit);
	
	if (hit.IsValidBlockingHit())
	{
		//if(actor) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, L"blocking hit");
		SlideAlongSurface(movement, 1.0f - hit.Time, hit.Normal, hit);
	}

	FVector gravity(0.0f, 0.0f, -10.0f);

	FHitResult gravHit;
	SafeMoveUpdatedComponent(gravity, UpdatedComponent->GetComponentQuat(), true, gravHit);
	if (gravHit.IsValidBlockingHit())
	{
		
	}

}