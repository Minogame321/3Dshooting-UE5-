// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "Kismet/GameplayStatics.h"



AEnemyBullet::AEnemyBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (flag) {
		FVector NowPosition = GetActorLocation();
		if (NowPosition.Y < LimitY) { Super::reborn(); }//ある位置を超えたら敵機に戻ってくる

		//前進
		AActor* Parent = GetParentActor();
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//親の移動を無視するために親子関係を解除
		Super::run(DeltaTime);
		//前進

	}
	else { Super::reborn();  }
}

