// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"

// Sets default values
APlanet::APlanet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();
	SetActorLocation(StartPosition);
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotation(DeltaTime);
}



void APlanet::Rotation(float DeltaTime) {
	AddActorLocalRotation(DeltaTime * RotationVelocity);
	//↓過剰開店に適応できない
	//FRotator CurrentRotation = GetActorRotation();
	//CurrentRotation += DeltaTime * RotationVelocity;
	//SetActorRotation(CurrentRotation);
	//UE_LOG(LogTemp,Display, TEXT("roatterotaterotate!!!!"))
}