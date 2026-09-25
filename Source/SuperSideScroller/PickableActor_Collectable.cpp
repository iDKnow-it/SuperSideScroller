// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Collectable.h"
#include "SuperSideScroller_Player.h"

void APickableActor_Collectable::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor_Collectable::PlayerPickUp(ASuperSideScroller_Player* Player)
{
	Super::PlayerPickUp(Player);

	Player->IncrementNumberOfCollectables(CollectableValue);
}
