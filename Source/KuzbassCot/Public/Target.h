// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

class UBoxComponent;

UENUM()
enum class EActivationDirection
{
	Both = 0,
	Forward,
	Backward
};

UCLASS()
class KUZBASSCOT_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	ATarget();

	void SetPreviousTarget(ATarget* Target) { PreviousTarget = Target; }
	void SetNextTarget(ATarget* Target) { NextTarget = Target; }

protected:
	UPROPERTY()
	USceneComponent* ActorRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* CollisionComponent;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Activation")
	UMaterialInstance* DefaultMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Activation")
	UMaterialInstance* ActiveMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Activation")
	FTimerHandle TimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Activation", meta = (ClampMin = 0.000001))
	float ActiveTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Activation")
	ATarget* PreviousTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Activation")
	ATarget* NextTarget;
	
	virtual void BeginPlay() override;

private:
	EActivationDirection ActivationDirection;
	
	void Activate(EActivationDirection IncomeDirection);
	void Deactivate();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
};
