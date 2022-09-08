// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTrack.h"

#include "Target.h"
#include "Components/SplineComponent.h"

ATargetTrack::ATargetTrack()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");
	SplineComponent->SetupAttachment(GetRootComponent());
}

void ATargetTrack::BeginPlay()
{
	Super::BeginPlay();

	if (!SplineComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
			FString("Spline component in null!"));
		return;
	}

	TArray<ATarget*> Targets;
	for (size_t i = 0; i < Count; i++)
	{
		const auto Time = (i + 1.f) / Count;
		auto Location = SplineComponent->GetLocationAtTime(Time, ESplineCoordinateSpace::World);
		const auto Target = GetWorld()->SpawnActor<ATarget>(Actor, FTransform(Location));
		Target->FinishSpawning(FTransform(Location));
		Targets.Add(Target);
	}

	ATarget* PreviousTarget = nullptr;
	for (const auto Target : Targets)
	{
		if (PreviousTarget)
		{
			Target->SetPreviousTarget(PreviousTarget);
			PreviousTarget->SetNextTarget(Target);
		}
		PreviousTarget = Target;
	}
}
