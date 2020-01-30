// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"
#include "HealthPotionItem.h"

void ACameraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Pawn = Cast<ACameraPawn>(GetPawn());

	HUD = Cast<AGameHUD>(GetHUD());
	HUD->CameraPawn = Pawn;

	SetTickableWhenPaused(true);
	ActionPause = false;
}

void ACameraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("CycleParty", IE_Pressed, this, &ACameraPlayerController::CyclePartyMember);
	InputComponent->BindAction("Select", IE_Released, this, &ACameraPlayerController::Select);
	InputComponent->BindAction("Space", IE_Pressed, this, &ACameraPlayerController::Space).bExecuteWhenPaused = true;
	InputComponent->BindAction("LeftFaceButton", IE_Pressed, this, &ACameraPlayerController::LeftFaceButton);
	InputComponent->BindAction("RightFaceButton", IE_Pressed, this, &ACameraPlayerController::RightFaceButton);
	InputComponent->BindAction("TopFaceButton", IE_Pressed, this, &ACameraPlayerController::TopFaceButton);

	InputComponent->BindAxis("MoveForward", this, &ACameraPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACameraPlayerController::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &ACameraPlayerController::PitchCamera).bExecuteWhenPaused = true;
	InputComponent->BindAxis("CameraYaw", this, &ACameraPlayerController::YawCamera).bExecuteWhenPaused = true;
	
}

void ACameraPlayerController::MoveForward(float Value)
{
	if (Pawn->Party[Pawn->PartyIndex]->attack)
	{
		Pawn->MovementInput.X = 0.0f;
		return;
	}
	float newValue = FMath::Clamp<float>(Value, -1.0f, 1.0f);
	Pawn->MovementInput.X = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void ACameraPlayerController::MoveRight(float Value)
{
	if (Pawn->Party[Pawn->PartyIndex]->attack)
	{
		Pawn->MovementInput.Y = 0.0f;
		return;
	}
	Pawn->MovementInput.Y = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void ACameraPlayerController::PitchCamera(float Value)
{
	if (!MenuPause) Pawn->CameraInput.Y = FMath::Clamp<float>(Value, -1.0f, 1.0f);
	else Pawn->CameraInput.Y = 0.0f;
}

void ACameraPlayerController::YawCamera(float Value)
{
	if (!MenuPause) Pawn->CameraInput.X = Value;
	else Pawn->CameraInput.X = 0.0f;
}

void ACameraPlayerController::CyclePartyMember()
{
	Pawn->Party[Pawn->PartyIndex]->Capsule->SetCollisionProfileName(TEXT("Pawn"));
	Pawn->Party[Pawn->PartyIndex]->IsPlayerControlledMember = false;
	Pawn->PartyIndex = (Pawn->PartyIndex + 1) % Pawn->Party.Num();
	Pawn->SetActorLocation(Pawn->Party[Pawn->PartyIndex]->GetActorLocation());
	Pawn->Party[Pawn->PartyIndex]->Capsule->SetCollisionProfileName(TEXT("PlayerControlled"));
	Pawn->Party[Pawn->PartyIndex]->IsPlayerControlledMember = true;

	HUD->SetPartyIndex(Pawn->PartyIndex);
}

void ACameraPlayerController::Select()
{
	Pawn->Party[Pawn->PartyIndex]->Target = 0;
	if (!Pawn->CreatureToSelect) return;
	Pawn->Party[Pawn->PartyIndex]->Target = Cast<ACreature>(Pawn->CreatureToSelect);
	
}

void ACameraPlayerController::Space()
{
	AWorldSettings* worldSettings = GetWorldSettings();
	//Time Dilation is set to 0.0 globally excluding the CameraPawn to create a pause where the
	//player can input orders and such.
	if (!MenuPause)
	{
		MenuPause = true;
		worldSettings->SetTimeDilation(0.0f);
		Pawn->CustomTimeDilation = 1.0f;
	}
	else
	{
		MenuPause = false;
		worldSettings->SetTimeDilation(1.0f);
	}
}

void ACameraPlayerController::LeftFaceButton()
{
	ACreature* ControlledCreature = Pawn->Party[Pawn->PartyIndex];
	ControlledCreature->ActionComponent->ExecuteLeftFaceButtonAction(ControlledCreature, ControlledCreature->Target);
}

void ACameraPlayerController::RightFaceButton()
{
	ACreature* ControlledCreature = Pawn->Party[Pawn->PartyIndex];
	ControlledCreature->ActionComponent->ExecuteRightFaceButtonAction(ControlledCreature, ControlledCreature->Target);
}

void ACameraPlayerController::TopFaceButton()
{
	ACreature* ControlledCreature = Pawn->Party[Pawn->PartyIndex];
	ControlledCreature->ActionComponent->ExecuteTopFaceButtonAction(ControlledCreature, ControlledCreature->Target);
}