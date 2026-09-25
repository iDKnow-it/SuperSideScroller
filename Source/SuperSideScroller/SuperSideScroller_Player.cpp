// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Player.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "PlayerProjectile.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"

ASuperSideScroller_Player::ASuperSideScroller_Player()
{
    bIsSprinting = false;

    GetCharacterMovement()->MaxWalkSpeed = 300.f; //设置默认最大速度
}

void ASuperSideScroller_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedPlayerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        APlayerController* PlayerController = Cast<APlayerController>(GetController());

        if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            EnhancedSubsystem->AddMappingContext(IC_Character, 1);

            EnhancedPlayerInput->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::Sprinting);
            EnhancedPlayerInput->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ASuperSideScroller_Player::StopSprinting);
            EnhancedPlayerInput->BindAction(IA_Throw, ETriggerEvent::Started, this, &ASuperSideScroller_Player::ThrowProjectile);
        }
    }

}

void ASuperSideScroller_Player::Sprinting()
{
    if (!bIsSprinting)
    {
        bIsSprinting = true;
        GetCharacterMovement()->MaxWalkSpeed = 500.f; //更新最大速度以实现冲刺
    }
}

void ASuperSideScroller_Player::StopSprinting()
{
    if (bIsSprinting)
    {
        bIsSprinting = false;
        GetCharacterMovement()->MaxWalkSpeed = 300.f; //更新最大速度以实现停止冲刺
    }
}

void ASuperSideScroller_Player::ThrowProjectile()
{
    if (ThrowMontage)
    {
        const bool bIsMontagePlaying = GetMesh()->GetAnimInstance()->Montage_IsPlaying(ThrowMontage);
        if (!bIsMontagePlaying)
        {
            GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage, 1.f);
        }
    }
}

void ASuperSideScroller_Player::SpawnProjectile()
{
    if (PlayerProjectile)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            const FVector SpawnLocation = this->GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
            const FRotator SpawnRotation = GetActorForwardVector().Rotation();

            APlayerProjectile* Projectile = World->SpawnActor<APlayerProjectile>(PlayerProjectile, SpawnLocation, SpawnRotation, SpawnParams);
        }
    }
}

void ASuperSideScroller_Player::IncrementNumberOfCollectables(int32 Value)
{
    if (Value == 0)
    {
        return;
    }
    else
    {
        NumberOfCollectables += Value;
    }
    UE_LOG(LogTemp, Warning, TEXT("Number of collectables: %d"), NumberOfCollectables);
}
