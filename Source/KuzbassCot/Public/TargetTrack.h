// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetTrack.generated.h"

class USplineComponent;
class ATarget;

UCLASS()
class KUZBASSCOT_API ATargetTrack : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetTrack();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	TSubclassOf<ATarget> Actor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	int32 Count;

protected:
	virtual void BeginPlay() override;
	
};
