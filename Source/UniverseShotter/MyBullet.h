// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "MyBullet.generated.h"

/**
 * 
 */
UCLASS()
class UNIVERSESHOTTER_API AMyBullet : public ABullet
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AMyBullet();

	virtual void Tick(float DeltaTime) override;
	FKey InputKey; //発射するためのキー入力を感知する.
	bool flag= false;//弾が発射中か否か

	//音を鳴らすために必要なコンポーネント達
	UAudioComponent* AudioComponent;
	USoundBase* SoundToPlay;
	//音を鳴らすために必要なコンポーネント達
};
