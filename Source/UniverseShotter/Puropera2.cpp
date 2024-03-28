// Fill out your copyright notice in the Description page of Project Settings.


#include "Puropera2.h"

// Sets default values
APuropera2::APuropera2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuropera2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuropera2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotation(DeltaTime);
}

void APuropera2::Rotation(float DeltaTime) {
	AddActorLocalRotation(DeltaTime * RotationVelocity);
}
