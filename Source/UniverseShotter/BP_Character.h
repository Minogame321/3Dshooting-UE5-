// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Character.generated.h"

UCLASS()
class UNIVERSESHOTTER_API ABP_Character : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	float Myx =0.0;
	UPROPERTY(EditAnywhere)
	float Myy = 0.0;
	UPROPERTY(EditAnywhere)
	float Myz = 0.0;
	UPROPERTY(EditAnywhere)
	float HitR = 100;
	UPROPERTY(EditAnywhere);
	float LimitScaleF = 6.0;
	float ScaleF = 1.05;
	int addscore = 100;
	int Score = 0;
	UPROPERTY(EditAnywhere);
	int HP = 500;
	float Explosionlife = 100;
	bool Death=false;
	FVector StartPosition = FVector(Myx,Myy,Myz);
	void MoveCharacter(float Deltatime);

	TArray<AActor*> FoundActors;
	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent;
	USoundBase* SoundToPlay;


	UPROPERTY(EditAnywhere)
	AActor* MyChildActor; // 子オブジェクトへの参照を保持するメンバ変数
};


