// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"


UCLASS()
class TOONTANKS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* BulletMovement;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & HitResult);

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticle;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* TrailParticle;

	UPROPERTY(EditAnywhere)
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

};
