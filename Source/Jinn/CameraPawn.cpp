// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PartyIndex = 0;
	CreatureToSelect = 0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 400.0f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	

	SelectionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SelectionWidget"));
	SelectionWidget->SetWidgetSpace(EWidgetSpace::World);

	TargetMarkerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TargetMarkerWidget"));
	TargetMarkerWidget->SetWidgetSpace(EWidgetSpace::World);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < Party.Num(); i++)
	{
		Party[i]->Player = this;
		Party[i]->SetTickableWhenPaused(true);
	}
	Party[PartyIndex]->Capsule->SetCollisionProfileName(TEXT("PlayerControlled"));
	
	SetTickableWhenPaused(true);
	CameraSpringArm->SetTickableWhenPaused(true);
	Camera->SetTickableWhenPaused(true);
}

void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		FRotator r = CameraSpringArm->RelativeRotation;
		r.Yaw += CameraInput.X;
		CameraSpringArm->SetRelativeRotation(r);
	}
	{
		FRotator r = CameraSpringArm->GetComponentRotation();
		r.Pitch = FMath::Clamp(r.Pitch + CameraInput.Y, -80.0f, 50.0f);
		CameraSpringArm->SetWorldRotation(r);
	}

	if (!MovementInput.IsZero())
	{
		MovementInput = MovementInput.GetSafeNormal() * 100.0f;
		FVector movement2D = Camera->GetForwardVector().GetSafeNormal2D() * MovementInput.X * DeltaTime;
		movement2D += Camera->GetRightVector().GetSafeNormal2D() * MovementInput.Y * DeltaTime;
		FVector newLocation = Party[PartyIndex]->GetActorLocation() + movement2D;
		//FVector newLocation = GetActorLocation() + movement2D;
		Party[PartyIndex]->GetMovementComponent()->AddInputVector(movement2D);

		
	}
	
	SetActorLocation(Party[PartyIndex]->GetActorLocation());

	FVector cameraForwardNormal = Camera->GetForwardVector().GetSafeNormal2D();
	FVector controlledPartyMemberLocation = Party[PartyIndex]->GetActorLocation();
	FVector traceStart = (cameraForwardNormal * 100.0)+controlledPartyMemberLocation;
	FVector traceEnd = (cameraForwardNormal * 1100.0) + controlledPartyMemberLocation;
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(Party[PartyIndex]);
	if (Party[PartyIndex]->Target) actorsToIgnore.Add(Party[PartyIndex]->Target);

	FHitResult hitResult;
	if (UKismetSystemLibrary::CapsuleTraceSingleByProfile(GetWorld(),
		traceStart, traceEnd, 100.0f, 0.0f,
		"Selection", false, actorsToIgnore,
		EDrawDebugTrace::None, hitResult, true)
	&&	hitResult.GetActor()
	&&	hitResult.GetActor()->GetClass()->IsChildOf(ACreature::StaticClass()))
	{
		if (CreatureToSelect)
		{
			if (!CreatureToSelect->GetName().Equals(hitResult.GetActor()->GetName()))
			{
				CreatureToSelect = Cast<ACreature>(hitResult.GetActor());
			}
		}
		else
		{
			CreatureToSelect = Cast<ACreature>(hitResult.GetActor());
		}
	}
	else
	{
		CreatureToSelect = 0;
	}

	if (CreatureToSelect)
	{
		if (CreatureToSelect != Party[PartyIndex]->Target)
		{
			SelectionWidget->SetVisibility(true);
			FVector targetToCamera = Camera->GetComponentLocation() - CreatureToSelect->GetActorLocation();
			SelectionWidget->SetWorldLocationAndRotation(CreatureToSelect->GetActorLocation(), targetToCamera.ToOrientationQuat());
		}
	}
	else
	{
		SelectionWidget->SetVisibility(false);
	}
	if (Party[PartyIndex]->Target)
	{
		TargetMarkerWidget->SetVisibility(true);
		FVector targetToCamera = Camera->GetComponentLocation() - Party[PartyIndex]->Target->GetActorLocation();
		TargetMarkerWidget->SetWorldLocationAndRotation(Party[PartyIndex]->Target->GetActorLocation(), targetToCamera.ToOrientationQuat());


	}
	else
	{
		TargetMarkerWidget->SetVisibility(false);
	}

}

void ACameraPawn::ApplyXP(float XP)
{
	for(int i = 0; i < Party.Num(); i++)
	{
		Party[i]->StatsComponent->AddExperience(XP);
	}
}