// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTrack.h"

// Sets default values
ATargetTrack::ATargetTrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetTrack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

