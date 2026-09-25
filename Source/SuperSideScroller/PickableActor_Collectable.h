// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableActor_Base.h"
#include "PickableActor_Collectable.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API APickableActor_Collectable : public APickableActor_Base
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Collectable") int32 CollectableValue = 1;//定义收集物价值

protected:

	virtual void PlayerPickUp(class ASuperSideScroller_Player* Player) override;

	virtual void BeginPlay() override;

private:
};
