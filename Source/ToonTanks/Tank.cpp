// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Tank.h"


ATank::ATank()
{

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed, this, &ATank::Fire);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(PlayerControllerRef)
    {
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            true,
            HitResult
        );
        RotateTurret(HitResult.ImpactPoint);
    }

}

APlayerController* ATank::GetPlayerControllerRef() const
{
    return PlayerControllerRef;
}


void ATank::Move(float Value)
{
FVector DeltaLocation(0.f);
DeltaLocation.X = Value*MovementSpeed*UGameplayStatics::GetWorldDeltaSeconds(this);
AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
FRotator DeltaRotation = FRotator::ZeroRotator;
DeltaRotation.Yaw = Value*TurningSpeed*UGameplayStatics::GetWorldDeltaSeconds(this);
AddActorLocalRotation(DeltaRotation, true);
}
