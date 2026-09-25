// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "SuperSideScroller_Player.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API ASuperSideScroller_Player : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()

public:
	ASuperSideScroller_Player();

	void ThrowProjectile();
	void SpawnProjectile();

	UFUNCTION(BlueprintPure) int32 GetNumberOfCollectables() { return NumberOfCollectables; }
	void IncrementNumberOfCollectables(int32 Value);

protected:
	//SetupPlayerInputComponent函数是ACharacter类中的一个虚函数，用于设置玩家输入组件。通过重写该函数，可以自定义玩家输入的绑定和处理逻辑。
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;//UInputComponent* PlayerInputComponent继承自父类的SetupPlayerInputComponent函数，用于设置玩家输入组件

	void Sprinting();
	void StopSprinting();

	UPROPERTY(EditAnywhere, Category = "Input") class UInputMappingContext* IC_Character;
	UPROPERTY(EditAnywhere, Category = "Input") class UInputAction* IA_Sprint;
	UPROPERTY(EditAnywhere, Category = "Input") class UInputAction* IA_Throw;

private:
	bool bIsSprinting;

	int32 NumberOfCollectables;

	UPROPERTY(EditAnywhere) class UAnimMontage* ThrowMontage;

	UPROPERTY(EditAnywhere) TSubclassOf<class APlayerProjectile> PlayerProjectile;
};
