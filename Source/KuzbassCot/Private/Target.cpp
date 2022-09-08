// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

#include "Components/BoxComponent.h"

ATarget::ATarget()
{
	PrimaryActorTick.bCanEverTick = false;

	ActorRootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(ActorRootComponent);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(GetRootComponent());
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
	
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("Collision");
	CollisionComponent->SetupAttachment(GetRootComponent());
	CollisionComponent->SetBoxExtent(FVector(50));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->SetNotifyRigidBodyCollision(true);

	CollisionComponent->OnComponentHit.AddDynamic(this, &ATarget::OnHit);
}

void ATarget::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->SetMaterial(0, DefaultMaterial);
}

void ATarget::Activate(const EActivationDirection IncomeDirection)
{
	ActivationDirection = IncomeDirection;
	if (TimerHandle.IsValid())
	{
		TimerHandle.Invalidate();
	}
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATarget::Deactivate, ActiveTime);
	MeshComponent->SetMaterial(0, ActiveMaterial);
}

void ATarget::Deactivate()
{
	TimerHandle.Invalidate();
	MeshComponent->SetMaterial(0, DefaultMaterial);

	switch(ActivationDirection)
	{
	case EActivationDirection::Both:
		if (NextTarget)
		{
			NextTarget->Activate(EActivationDirection::Forward);
		}
		if (PreviousTarget)
		{
			PreviousTarget->Activate(EActivationDirection::Backward);
		}
		break;
	case EActivationDirection::Forward:
		if (NextTarget)
		{
			NextTarget->Activate(EActivationDirection::Forward);
		}
		break;
	case EActivationDirection::Backward:
		if (PreviousTarget)
		{
			PreviousTarget->Activate(EActivationDirection::Backward);
		}
		break;
	}
}

void ATarget::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Activate(EActivationDirection::Both);
}
