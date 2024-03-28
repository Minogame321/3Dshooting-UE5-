// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include <iostream>
#include<math.h>
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
using namespace std;


// Sets default values
AEnemy::AEnemy()
{

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//爆発音を鳴らすためのコンポーネント
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetVolumeMultiplier(0.0f);
	SoundToPlay = LoadObject<USoundBase>(nullptr, TEXT("SoundCue'/Game/StarterContent/explosionqueue.explosionqueue'"));
	AudioComponent->SetSound(SoundToPlay);
	//爆発音を鳴らすためのコンポーネント
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("bullet"), FoundActors);//弾を格納
	//自プレイヤーを格納
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), MyActors);
	MyActor = Cast<ABP_Character>(MyActors[0]);
	//自プレイヤーを格納
	Spawn();//初期位置に設定
	if (ActorHasTag("Rare")) { Death = true; }//レアキャラは最初は撃墜状態
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotation(DeltaTime);//回転しながら
	Run(DeltaTime);//移動
}



void AEnemy::Rotation(float DeltaTime) {
	AddActorLocalRotation(DeltaTime * RotationVelocity);
}

void AEnemy::Run(float DeltaTime) {
	AActor* MyBullet = FoundActors[0]; 
	FVector BulletLocation = MyBullet->GetActorLocation();
	FVector NowPosition = GetActorLocation();

	float difx = pow((BulletLocation.X - NowPosition.X), 2.0);
	float dify = pow((BulletLocation.Y - NowPosition.Y), 2.0);
	float difz = pow((BulletLocation.Z - NowPosition.Z), 2.0);

	if (sqrt(difx + dify + difz) < HitR && !Death) {//プレイヤーの弾との当たり判定
		Death = true;
		AudioComponent->Play();
		if(ActorHasTag("Rare")){ MyActor->Score += 500; }//レアキャラなら+500
		else{//通常キャラなら+100
			MyActor->Score += 100; 
			int x = rand() % 20 + 1;
			if (x == 1) {
				TArray<AActor*> FoundRares;
				UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Rare"), FoundRares);
				AEnemy* RareCharacter =Cast <AEnemy>( FoundRares[0]);

				RareCharacter->Death = false;
			}

		}
		
	}
	else {//プレイヤーの弾と当たっていない時
		if(!Death){//非撃墜時
				for (AActor* FoundExplosion : FoundExplosions)
				{

					if (FoundExplosion->ActorHasTag("Explosion")) {
							FVector NewScale = { 1.0,1.0,1.0 };
							FoundExplosion->SetActorScale3D(NewScale);
					}

				}
			nowtheta += theta;//回転しながら
			MoveValue.Z = sinpuku * sin(nowtheta * 3.141592665 / 360.0);
			NowPosition += DeltaTime * MoveValue;//移動
			SetActorLocation(NowPosition);
			if ((direction == 0 && NowPosition.X < -3200) || (direction == 1 && NowPosition.X > 2500)) { Spawn(); }//画面外にいったらスポーン
		}
		else {//撃墜時
			GetAttachedActors(FoundExplosions); // すべての子アクターを取得
			
			//名前上Explosionsだけど、自分の弾についても処理
			for (AActor* FoundExplosion : FoundExplosions)
			{	
					// タグが付いたActorのスケールを変更
				if (FoundExplosion->ActorHasTag("Explosion")) {
					FVector NewScale = FoundExplosion->GetActorScale3D() * ScaleF;
					if (NewScale.X < LimitScaleF) {
						FoundExplosion->SetActorScale3D(NewScale);//爆発エフェクトを拡大
					}
					else {
						ExplosionLife -= 5.0;
						if(ExplosionLife<=0){//爆発エフェクトが限界まで膨らんだらスポーン
							NewScale = { 0.8,0.8,0.8 };
							FoundExplosion->SetActorScale3D(NewScale);
							Spawn(); 
						}
							
					}
				}
				else if (FoundExplosion->ActorHasTag("EnemyBullet")) {//弾は非発射状態に
					AEnemyBullet* FoundBullet = Cast<AEnemyBullet>(FoundExplosion);
					FoundBullet->flag = false;
				}

			}

		}
	}
}



void AEnemy::Spawn() {
	GetAttachedActors(FoundExplosions); // すべての子アクターを取得
	for (AActor* FoundExplosion : FoundExplosions)//全ての弾を発射状態に
	{
		if (FoundExplosion->ActorHasTag("EnemyBullet")) {
			AEnemyBullet* FoundBullet = Cast<AEnemyBullet>(FoundExplosion);
			FoundBullet->flag = true;
		}

	}


	if (ActorHasTag("Rare")) { Death = true; }//レアキャラは撃墜状態に
	else{ Death = false; }//他は非撃墜状態に
	
	//その他値の初期化

	ExplosionLife = 100;
	FVector NowPosition = GetActorLocation();
	direction = rand() % 2;
	if (direction == 0) { NowPosition.X = 2500; }
	else { NowPosition.X = -3200; }
	NowPosition.Z = rand() % 650 - 390;
	SetActorLocation(NowPosition);

	MoveValue.X = rand() % (int)MaxVelocity.X + 250;
	if (direction == 0) { MoveValue.X *= -1; }
	nowtheta = 0;
	sinpuku = rand() % (int)MaxVelocity.Z + 1;
	MoveValue.Z = sinpuku * sin(nowtheta * 3.141592665 / 360.0);
}


