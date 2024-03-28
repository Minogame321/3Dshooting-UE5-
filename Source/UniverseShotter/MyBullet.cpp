// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBullet.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


AMyBullet::AMyBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//発射音を鳴らすための設定
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	float Volume = 1.0f; 
	AudioComponent->SetVolumeMultiplier(Volume);
	FVector SoundLocation = FVector(0, 0, 0); 
	AudioComponent->SetWorldLocation(SoundLocation);
	SoundToPlay = LoadObject<USoundBase>(nullptr, TEXT("SoundCue'/Game/StarterContent/shootqueue.shootqueue'"));
	AudioComponent->SetSound(SoundToPlay);
	//発射音を鳴らすための設定
}



// Called every frame
void AMyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (PC->IsInputKeyDown(EKeys::A) && !flag)//Aキーが入力されたら
		 {
			 flag = true;//発射中状態に変更
			 AudioComponent->Play();//発射音を鳴らす

		 }
	}
	
	FVector NowPosition = GetActorLocation();
	if (NowPosition.Y > LimitY && flag) { flag = false; Super::reborn(); }//限界位置を超えたら主人公気に戻ってくる
	if (flag) {
		Super::run(DeltaTime);//限界位置にたどりついていない場合前進
	}

}
