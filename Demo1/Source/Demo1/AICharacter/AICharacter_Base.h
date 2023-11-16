// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Demo1/Manager/GeneralDataAsset.h"
#include "BehaviorTree/BehaviorTree.h"

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

	void Tick(float DeltaSeconds) override;

	UFUNCTION()
	ECampType GetCampType();

	UFUNCTION()
	void SetCampType(ECampType CampType);

	UFUNCTION()
	ESoldierType GetSoldierType();

	UFUNCTION()
	UBehaviorTree* GetBTree();

	UFUNCTION(BlueprintCallable)
	void UpdateWalkSpeed();
	
	UFUNCTION()
	AAICharacter_Base* GetLockedEnemy();

	UFUNCTION()
	void SetLockedEnemy(AAICharacter_Base* Enemy);
	
	UFUNCTION()
	bool IsAttack();

	UFUNCTION()
	void UpdateAttackState();

public:
	// 最大生命值
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float MaxHP;

	// 攻击力
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float Atk;

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

	// 攻击方式（直接放在派生类就行）

	// 当前兵种的类型
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	ESoldierType SoldierType;

	// 当前 AI 使用的行为树
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	UBehaviorTree* BTree = nullptr;

	// 选敌规则
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	EEnemySelectRule EnemySelectRule;

	// 感知半径（发现敌人的范围，发起追击）
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float PerceptionRadius;

	// 离开感知的半径
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float LosePerceptionRadius;
	
	// 攻击范围（追击敌人到此范围内的时候就发起攻击）
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float AttackRadius;

private:
	// 当前生命值
	UPROPERTY()
	float M_CurrentHP;

	// 属于哪个阵营
	UPROPERTY()
	ECampType M_CampType;

	// 当前 AI 锁定到的 Enemy AI
	UPROPERTY()
	AAICharacter_Base* M_LockedEnemy = nullptr;
};
