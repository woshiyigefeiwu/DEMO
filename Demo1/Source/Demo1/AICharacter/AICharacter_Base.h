// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Demo1/Manager/GeneralDataAsset.h"

#include "CoreMinimal.h"
#include "Demo1/Demo1Character.h"
#include "AICharacter_Base.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API AAICharacter_Base : public ADemo1Character
{
	GENERATED_BODY()
	
public:
	AAICharacter_Base();

protected:
	// 最大生命值
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float MaxHP;

	// 攻击力
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float Atk;

	// 攻击方式（这个比较麻烦...）


	// 攻击 CD
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float AtkCD;

	// 移动速度
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float MoveSpeed;

	// 碰撞体积
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	FVector CollisionVolume;

	// 显示的图片
	UPROPERTY(EditAnywhere, Category = "BaseConfig", meta = (AllowedClasses = "Texture"))
	FSoftObjectPath ShowImage;

	// 旋转速度
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float RotateSpeed;

private:
	// 当前生命值
	float M_CurrentHP;

	// 属于哪个阵营
	ECampType M_Camp;
};
