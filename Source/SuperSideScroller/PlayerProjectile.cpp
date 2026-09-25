// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBase.h"

// Sets default values
APlayerProjectile::APlayerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(15.0f);//设置碰撞半径
	CollisionComp->BodyInstance.SetCollisionProfileName("BlockAll");
	CollisionComp->OnComponentHit.AddDynamic(this, &APlayerProjectile::OnHit);//设置碰撞事件
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->InitialSpeed = 800.f;//设置初始速度
	ProjectileMovement->MaxSpeed = 800.f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	InitialLifeSpan = 3.f;//设置生命周期
}

void APlayerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Projectile hit: %s"), *OtherActor->GetName());
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	if (Enemy)
	{
		Enemy->DestroyEnemy();
	}
    ExplodeProjectile();
}

void APlayerProjectile::ExplodeProjectile()
{
	Destroy();
}

