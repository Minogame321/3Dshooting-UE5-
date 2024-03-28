// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EnemyBullet.h"
#include "BP_Character.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class UNIVERSESHOTTER_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere);
	FRotator RotationVelocity;
	UPROPERTY(EditAnywhere);
	FVector MaxVelocity = {500,0,500};
	UPROPERTY(EditAnywhere);
	float theta=10.0;
	float nowtheta = 10.0;

	float sinpuku=500;


	FVector MoveValue;
	TArray<AActor*> FoundExplosions;

	UPROPERTY(EditAnywhere);
	AActor* OtherActor;
	UPROPERTY(EditAnywhere);
	float HitR = 200;

	UPROPERTY(EditAnywhere);
	float ExplosionLife = 100;
	UPROPERTY(EditAnywhere);
	float ScaleF = 1.05;
	UPROPERTY(EditAnywhere);
	float LimitScaleF = 5.0;
	UPROPERTY(EditAnywhere);
	UAudioComponent* AudioComponent;
	USoundBase* SoundToPlay;

	bool Death = false;
	TArray<AActor*> MyActors;
	ABP_Character* MyActor;
	UStaticMeshComponent* MeshComponent = FindComponentByClass<UStaticMeshComponent>();

	TArray<AActor*> FoundActors;

	int direction;

	void Rotation(float DeltaTime);
	void Spawn();
	void Run(float DeltaTime);



};

