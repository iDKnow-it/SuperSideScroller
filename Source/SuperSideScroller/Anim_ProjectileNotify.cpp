// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_ProjectileNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "SuperSideScroller_Player.h"

void UAnim_ProjectileNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);//调用继承自父类的函数，确保功能执行
	ASuperSideScroller_Player* Player = Cast<ASuperSideScroller_Player>(MeshComp->GetOwner());
	if (Player)
	{
		Player->SpawnProjectile();
	}
}
