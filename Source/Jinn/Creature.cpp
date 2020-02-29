// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"
#include "CameraPawn.h"
#include "LootDrop.h"
#include "CameraPlayerController.h"

// Sets default values
ACreature::ACreature()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->InitCapsuleSize(40.0f, 60.0f);
	Capsule->SetCollisionProfileName(TEXT("Pawn"));

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	MeshComponent->SetupAttachment(RootComponent);

	TargetComponent = CreateDefaultSubobject<USceneComponent>(L"TargetComponent");
	TargetComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UCreatureMovementComponent>(TEXT("CreatureMovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	ActionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(L"StatsComponent");

	AttackRange = 500.0f;
	XPWorth = 0.0f;
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ACameraPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	IsPartyMember = Player->Party.Contains(this);

	DeathTime = 0.0f;

	if (IsPartyMember)
	{
		IsPlayerControlledMember = (Player->Party[Player->PartyIndex] == this);
	}
	else
	{
		IsPlayerControlledMember = false;
	}
}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsPartyMember && State == EState::Dead)
	{
		if (DeathTime > 20.0f)
		{
			Destroy();
			return;
		}
		DeathTime += DeltaTime;
	}

	ACameraPlayerController* controller = Cast<ACameraPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!controller->ActionPause && !controller->MenuPause)
	{
		FVector velocity = GetVelocity();
		velocity.Z = 0.0f;
		if (!velocity.IsZero() && !velocity.IsNearlyZero())
		{
			SetActorRotation(velocity.ToOrientationQuat());
		}
	}

	if (Target != 0)
	{
		if (Target->GetClass()->IsChildOf(ACreature::StaticClass()))
		{
			
			if (Cast<ACreature>(Target)->State == EState::Dead)
			{
				Target = 0;
			}
		}
	}

	for (int32 i = 0; i < StatusEffects.Num(); i++)
	{
		StatusEffects[i]->Effects(this, DeltaTime);
	}
	if (StatusEffectTag & 1)
	{
		MeshComponent->bPauseAnims = true;
	}
	else
	{
		MeshComponent->bPauseAnims = false;
	}
	if (!(StatusEffectTag & 8))
	{	
		CustomTimeDilation = 1.0f;
	}
	if (!(StatusEffectTag & 16))
	{
		StatsComponent->EffectiveAccuracy = StatsComponent->Accuracy;
	}
	if (StatsComponent->Will > StatsComponent->MaxWill)
	{
		StatusEffectTag |= 4;
	}
	else if (StatusEffectTag & 4)
	{
		StatusEffectTag &= ~4;
	}
}

// Called to bind functionality to input
void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UPawnMovementComponent* ACreature::GetMovementComponent() const
{
	return MovementComponent;
}

bool ACreature::IsCloseToPlayer()
{
	return FVector::Dist(Player->GetActorLocation(), GetActorLocation()) < 600.0f;
}

float ACreature::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	ACreature* Source = Cast<ACreature>(DamageCauser);
	if (Source)
	{
		if (State != EState::Agro)
		{
			State = EState::Agro;
		}

		if (!Target)
		{
			Target = Source;
		}
	}

	StatsComponent->Health -= DamageAmount;
	if (StatsComponent->Health <= 0)
	{
		State = EState::Dead;
		Capsule->SetCollisionProfileName(L"IgnoreOnlyPawn");
		if (Allegiance == EAllegiance::Enemy) Player->ApplyXP(XPWorth);
		if (DropClass)
		{
			FActorSpawnParameters params;
			UWorld* world = GetWorld();
			if (!world) return NULL;
			FVector loc = GetActorLocation();
			loc.Z -= 90;
			FRotator rot = GetActorRotation();
			ALootDrop* drop = Cast<ALootDrop>(world->SpawnActor(DropClass, &loc, &rot, params));
			drop->DisplayText = DisplayName;
			drop->Inventory = ItemsToDrop;
		}
	}
	return DamageAmount;
}

bool ACreature::StatusEffectBitwiseAnd(uint8 value)
{
	return (StatusEffectTag & value) != 0;
}