// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	public:

	void ActorDied(AActor* DeadActor);

	protected:
	
	virtual void BeginPlay() override;	
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	private:

	void HandleGameStart();

	class ATank* Tank;
	class AToonTankPlayerController* ToonTankPlayerController;

	float StartDelay = 3.f;
	int32 TargetTower = 0;
	int32 GetTargetTowerCount();
};
