// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BP_Character.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Engine/font.h"
#include "Score.generated.h"

UCLASS()
class UNIVERSESHOTTER_API AScore : public AHUD
{
	GENERATED_BODY()

	int HP=100;
	int Score = 0;
	UPROPERTY()
	UFont* HUDFont;
	void DrawHUD();
	UFont* Font;  // 追加

	TArray<AActor*> MyActors;
	ABP_Character* MyActor;
};





