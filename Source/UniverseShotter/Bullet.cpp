// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SceneComponent.h"
// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

}



void ABullet::run(float DeltaTime) {//座標を得て、そこにMovevalueを足して座標更新
	FVector NowPosition = GetActorLocation();
	NowPosition += Movevalue;
	
	SceneComponent->SetWorldLocation(NowPosition);
}



void ABullet::reborn() {//親の座標を得て、そこに新しく座標を設定する
	if(ActorHasTag("EnemyBullet")){ Movevalue.Y = -rand() % 60 - 2.5; }//敵の弾なら速度にランダム性を持たせる
    FVector ParentActorLocation = GetParentActor()->GetActorLocation();
    SetActorLocation(ParentActorLocation);

}
