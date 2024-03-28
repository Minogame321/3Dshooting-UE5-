// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Character.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABP_Character::ABP_Character()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//爆発音を鳴らすための設定
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	float Volume = 1.0f; // 例: ボリュームを0.5に設定
	AudioComponent->SetVolumeMultiplier(Volume);
	SoundToPlay = LoadObject<USoundBase>(nullptr, TEXT("SoundCue'/Game/StarterContent/explosionqueue.explosionqueue'"));
	AudioComponent->SetSound(SoundToPlay);
	//爆発音を鳴らすための設定
}

// Called when the game starts or when spawned
void ABP_Character::BeginPlay()
{
	Super::BeginPlay();
	StartPosition=GetActorLocation();
	Myx = StartPosition.X;
	Myy = StartPosition.Y;
	Myz = StartPosition.Z;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("EnemyBullet"), FoundActors);//敵機の弾の座標を取得


}

// Called every frame
void ABP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCharacter(DeltaTime);//移動処理
}

void ABP_Character::MoveCharacter(float DeltaTime) {
	FVector CurrentLocation = GetActorLocation();
	int i = 0;
	while (i<FoundActors.Num()) {//全敵機都のあたり判定を考慮
		AActor* MyBullet = FoundActors[i]; // 一つの"MyBullet"アクターを取得
		FVector BulletLocation = MyBullet->GetActorLocation();
		float difx = pow((BulletLocation.X - CurrentLocation.X), 2.0);
		float dify = pow((BulletLocation.Y - CurrentLocation.Y), 2.0);
		float difz = pow((BulletLocation.Z - CurrentLocation.Z), 2.0);

		

		if (sqrt(difx + dify + difz) < HitR) { HP -= 10;  if (HP <= 0) { AudioComponent->Play(); Death = true; } }//当たっていたらHP減少
		i += 1;
	}
	// プレイヤーコントローラー取得
	if (!Death) {//プレイヤーが非撃墜時はマウスによって座標が変化
		TObjectPtr< APlayerController> aPlayerController = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
		// マウス座標の取得
		float aMousePositionX;
		float aMousePositionZ;
		aPlayerController->GetMousePosition(aMousePositionX, aMousePositionZ);
		Myx = aMousePositionX / 1920 * 1500;
		Myz = aMousePositionZ / 1080 * 750;
		FVector NowPosition = FVector(-(Myx - 200), 0, -(Myz - 310));
		SetActorLocation(NowPosition);
	}
	else {//撃墜時処理
		TArray<AActor*> FoundExplosions;
		GetAttachedActors(FoundExplosions); // すべての子アクターを取得

		//名前上Explosionsだけど、自分の弾についても処理
		for (AActor* FoundExplosion : FoundExplosions)
		{
			// タグが付いたActorのスケールを変更
			if (FoundExplosion->ActorHasTag("Explosion")) {//撃墜時は中の爆風を拡大していく
				FVector NewScale = FoundExplosion->GetActorScale3D() * ScaleF;
				if (NewScale.X < LimitScaleF) {
					FoundExplosion->SetActorScale3D(NewScale);
				}
				else {
					Explosionlife -= 5.0;
					if (Explosionlife <= 0) {//ある程度爆風が膨らんだら非表示にする
						Myx = 1000000000; FVector NowPosition = FVector(Myx, 0, 0); SetActorLocation(NowPosition);
					}

				}
			}
		}
	}
}
	

