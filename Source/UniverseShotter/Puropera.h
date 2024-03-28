// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puropera.generated.h"

UCLASS()
class UNIVERSESHOTTER_API APuropera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuropera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	FRotator RotationVelocity;
	void Rotation(float Deltatime);
};
