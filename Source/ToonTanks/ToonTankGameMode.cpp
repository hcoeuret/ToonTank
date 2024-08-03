// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTankPlayerController.h"
#include "ToonTankGameMode.h"

void AToonTankGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(ToonTankPlayerController)
        {
            ToonTankPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if(ATower * DeadTower = Cast<ATower>(DeadActor)){
        DeadTower->HandleDestruction();
        TargetTower--;
        if(TargetTower == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTankGameMode::HandleGameStart()
{
    TargetTower = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    ToonTankPlayerController->SetPlayerEnabledState(false);

    FTimerHandle PlayerEnabledTimerHandle;
    FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(
        ToonTankPlayerController,
        &AToonTankPlayerController::SetPlayerEnabledState, 
        true
        );
    GetWorldTimerManager().SetTimer(PlayerEnabledTimerHandle, PlayerEnabledTimerDelegate, StartDelay, false);
}

int32 AToonTankGameMode::GetTargetTowerCount()
{
    TArray<AActor *> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}