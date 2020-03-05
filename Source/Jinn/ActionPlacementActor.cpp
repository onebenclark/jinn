// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlacementActor.h"

// Sets default values
AActionPlacementActor::AActionPlacementActor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->InitCapsuleSize(1.0f, 60.0f);
	Capsule->SetCollisionProfileName(TEXT("Control"));
	RootComponent = Capsule;
	
	

	MovementComponent = CreateDefaultSubobject<UCreatureMovementComponent>(TEXT("CreatureMovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	ActionPlacementWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionPlacementWidget"));
	ActionPlacementWidget->SetWidgetSpace(EWidgetSpace::World);
	ActionPlacementWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AActionPlacementActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActionPlacementActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AActionPlacementActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UPawnMovementComponent* AActionPlacementActor::GetMovementComponent() const
{
	return MovementComponent;
}