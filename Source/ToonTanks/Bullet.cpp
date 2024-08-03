// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	RootComponent = BulletMesh;

	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Particle"));
	TrailParticle->SetupAttachment(RootComponent);

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Bullet Movement"));
	BulletMovement->InitialSpeed = 40.f;
	BulletMovement->MaxSpeed = 50.f;
	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	if(FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation(), 1.0, 0.5);
	}

	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & HitResult)
{
	AActor * MyOwner = GetOwner();
	if(MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();

	if(OtherActor && OtherActor != this && OtherActor != MyOwner){
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, UDamageType::StaticClass());
		if(HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, this->GetActorLocation(), this->GetActorRotation());
		}
		if(HitSound)
		{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		if(HitCameraShakeClass)
		{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
		
	Destroy();
}



