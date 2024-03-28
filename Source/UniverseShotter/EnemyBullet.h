// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Bullet.h"
#include "EnemyBullet.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSESHOTTER_API AEnemyBullet : public ABullet
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AEnemyBullet();
	
	bool flag = true;//発射中かどうか

	virtual void Tick(float DeltaTime) override;


};
