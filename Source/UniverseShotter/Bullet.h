// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class UNIVERSESHOTTER_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UPROPERTY(EditAnywhere)
	FVector Movevalue; //移動量の定義
	UPROPERTY(EditAnywhere)
	float LimitY=500; //移動できる座標の制限

	USceneComponent* SceneComponent;



	virtual void run(float DeltaTime);
	virtual void reborn();
};
