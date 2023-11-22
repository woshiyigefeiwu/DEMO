// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Demo1/Manager/GeneralDataAsset.h"
#include "BehaviorTree/BehaviorTree.h"

#include "CoreMinimal.h"
#include "Demo1/Demo1Character.h"
#include "AICharacter_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLaunchAttack);		// 发起攻击
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindTargetFinish);	// 找完 Target 之后

UCLASS()
class DEMO1_API AAICharacter_Base : public ADemo1Character
{
	GENERATED_BODY()
	
public:
	AAICharacter_Base();

	void Tick(float DeltaSeconds) override;

// ----------------------------------------- Init，Get，Set，Check 函数 ----------------------------------------------
public:
	// 初始化一些 AI 的属性
	UFUNCTION()
	virtual void Init();

	// 获取当前 AI 的阵营类型
	UFUNCTION()
	ECampType GetCampType();

	// 设置 AI 的阵营类型
	UFUNCTION()
	void SetCampType(ECampType CampType);

	// 获取当前 AI 属于什么兵种
	UFUNCTION()
	ESoldierType GetSoldierType();

	// 获取一下当前 AI 执行的行为树
	UFUNCTION()
	UBehaviorTree* GetBTree();

	// 判断是否在攻击状态
	UFUNCTION()
	bool IsAttack();

	// 判断是否死亡
	UFUNCTION()
	bool IsDead();

	// 设置一下当前 HP
	UFUNCTION()
	float SetCurrentHP(float NewHP);

	// 获取当前 AI 的目标敌人
	AAICharacter_Base* GetTargetEnemy();

	// 设置当前 AI 的目标敌人
	void SetTargetEnemy(AAICharacter_Base* NewEnemy);

	// 获取 Enemy 数组
	TArray<AAICharacter_Base*> GetEnemyArray();

// ------------------------------------------- 辅助函数 -----------------------------------
public:
	// 更新一下 AI 的行走速度
	UFUNCTION(BlueprintCallable)
	void UpdateWalkSpeed();

	// 受到攻击（从APawn覆盖）
	UFUNCTION()
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// 选敌（根据选敌规则调用不同的选敌方式）
	UFUNCTION()
	AAICharacter_Base* SelectTarget();

	// 找第一个发现的敌人（派生类可自己重写）
	virtual AAICharacter_Base* SelectTarget_First();

	// 找距离最近的敌人（派生类可自己重写）
	virtual AAICharacter_Base* SelectTarget_Nearest();

	// AI 死亡后的处理
	UFUNCTION()
	void AIDead();

	// 清空定时器
	UFUNCTION()
	void ClearTimerHandle();

	// 是否正在CD中
	UFUNCTION(BlueprintCallable)
	bool IsInAttackCD();

	// 求和目标的距离
	UFUNCTION(BlueprintCallable)
	float GetDistanceFromEnemy();

// ---------------------------------------- AI Behavior 接口（BT 调用） ------------------------------------------------
public:
	// 发起攻击（派生类重写一下）
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	virtual void AttackEnemy();

	// 寻找敌人
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	virtual void FindTarget();

	// 进入攻击 CD
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	void EntryAttackCD();

	// 施加伤害
	UFUNCTION(BlueprintCallable)
	void AI_ApplyDamage();

// ----------------------------------------- AI 的基础属性 --------------------------------------------
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

protected:
	// 当前生命值
	UPROPERTY()
	float M_CurrentHP;

	// 属于哪个阵营
	UPROPERTY()
	ECampType M_CampType;

	// 是否属于死亡状态
	UPROPERTY()
	bool M_IsDead = false;
	
// --------------------------------------- AI 相关的数据 ----------------------------------
private:
	// 定时器，用于处理攻击CD
	UPROPERTY()
	FTimerHandle M_TimerHandle;

	// 当前 AI 的 目标敌人（同步黑板键值）
	UPROPERTY()
	AAICharacter_Base* M_TargetEnemy = nullptr;

	// 当前 AI 是否处于攻击状态（同步黑板键值）
	bool M_IsAttack;

public:
	// 检测到的敌人
	UPROPERTY()
	TArray<AAICharacter_Base*> EnemyArray;

// ---------------------------------------- Delegate --------------------------------------
public:
	// 寻找完目标之后，抛个事件
	UPROPERTY()
	FOnFindTargetFinish OnFindTargetFinish;

	// 发起攻击
	UPROPERTY(BlueprintAssignable)
	FOnLaunchAttack OnLaunchAttack;
};
