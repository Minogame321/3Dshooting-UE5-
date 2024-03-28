// Score.cpp
#include "Score.h"
#include "Engine/Canvas.h"
#include"GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"

void AScore::DrawHUD()
{
    Super::DrawHUD();

    // スコアの値を取得（この部分はあなたのスコア管理システムに合わせて変更してください）

    //スコア値を表示(プレイヤーが持つ変数スコアを参照)
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), MyActors);
    MyActor = Cast<ABP_Character>(MyActors[0]);
    FString ScoreText = FString::Printf(TEXT("Score: %d"), MyActor->Score);
    float TextX = 10.0f;
    float TextY = 10.0f;
    float TextScale = 8.0f;
    DrawText(ScoreText, FColor::White, TextX, TextY, nullptr, TextScale);
    //スコア値を表示(プレイヤーが持つ変数スコアを参照)


    //プレイヤーのHPを表示
    ScoreText = FString::Printf(TEXT("HP: %d"), MyActor->HP);
    TextX = 1500.0f;
    DrawText(ScoreText, FColor::White, TextX, TextY, nullptr, TextScale);
    //プレイヤーのHPを表示

    if (MyActor->Death) {//プレイヤー死亡時に"Game over"とスコアを表示する
         TextX = 750.0f;
         TextY = 540.0f;
         ScoreText = FString::Printf(TEXT("GAME OVER"));
         DrawText(ScoreText, FColor::Red, TextX, TextY, nullptr, TextScale);
         TextX = 800.0f;
         TextY = 740.0f;
         ScoreText = FString::Printf(TEXT("Score: %d"), MyActor->Score);
         DrawText(ScoreText, FColor::Red, TextX, TextY, nullptr, TextScale);
    }

}


