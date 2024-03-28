// Fill out your copyright notice in the Description page of Project Settings.


#include "Puropera.h"

// Sets default values
APuropera::APuropera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuropera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuropera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotation(DeltaTime);
}

void APuropera::Rotation(float DeltaTime) {
	AddActorLocalRotation(DeltaTime * RotationVelocity);
}