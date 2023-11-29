// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Demo1/Manager/GeneralDataAsset.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Demo1/Skill/SkillComponent.h"

#include "CoreMinimal.h"
#include "Demo1/Demo1Character.h"
#include "AICharacter_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAfterPossessed);		//
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLaunchAttack);		// 发起攻击
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeDamage);			// 受到伤害（刷一下 UI 等等）
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAIDead);				// 角色死亡
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangeHp);			// 血量改变

UCLASS()
class DEMO1_API AAICharacter_Base : public ADemo1Character
{
	GENERATED_BODY()
	
public:
	AAICharacter_Base();

	void Tick(float DeltaSeconds) override;

	void BeginPlay() override;

// ----------------------------------------- Init，Get，Set，Check 函数 ----------------------------------------------
public:
	// 初始化一些 AI 的属性（时机：AIC OnPossess 时）
	UFUNCTION()
	virtual void Init();

	// 蓝图重写，提供给蓝图去初始化一些东西（时机：BeginPlay）
	UFUNCTION(BlueprintImplementableEvent)
	void Init_BP();

	// 获取当前 AI 的阵营类型
	UFUNCTION()
	ECampType GetCampType();

	// 获取当前阵营对应的颜色
	UFUNCTION(BlueprintCallable)
	FColor GetColorByCampType();

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

	// 获取攻击力
	UFUNCTION()
	float GetAtk();

	// 获取最大生命值
	UFUNCTION(BlueprintCallable)
	float GetMaxHp() { return MaxHP; }

	// 获取当前生命值
	UFUNCTION(BlueprintCallable)
	float GetCurrentHp() { return M_CurrentHP; }

	// 设置一下当前 HP
	UFUNCTION()
	float SetCurrentHP(float NewHP);

	// 获取显示的图片
	UFUNCTION(BlueprintCallable)
	FString GetImagePath();

	// 获取显示的文本
	UFUNCTION(BlueprintCallable)
	FString GetDisplayStr() {return DisplayStr;}

	// 设置技能组件
	UFUNCTION()
	void SetSkillComponent(USkillComponent* NewSkillComponent);

// ------------------------------------------- 辅助函数 -----------------------------------
public:
	// 更新一下 AI 的行走速度
	UFUNCTION(BlueprintCallable)
	void UpdateWalkSpeed();

	// 受到攻击（从APawn覆盖）
	UFUNCTION()
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// AI 死亡后的处理
	UFUNCTION()
	void AIDead();

	// 清空定时器
	UFUNCTION()
	void ClearTimerHandle();

	// 是否正在CD中
	UFUNCTION(BlueprintCallable)
	bool IsInAttackCD();

	// 尝试触发触发条件为hp的技能
	UFUNCTION(BlueprintCallable)
	void TryExecuteSkillWhenHp();

// ---------------------------------------- AI Behavior 接口（BT 调用） ------------------------------------------------
public:
	// 发起攻击（派生类重写一下）
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	virtual void AttackEnemy(AAICharacter_Base* Enemy);

	// 寻找敌人
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	virtual void FindTarget();

	// 进入攻击 CD
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	void EntryAttackCD();

	// 是否能对 Actor 造成伤害
	UFUNCTION(BlueprintCallable)
	bool IsCanApplyDamage(AActor* Target);

	// 对 AI 造成伤害
	UFUNCTION(BlueprintCallable)
	void ApplyDamageToAI(AActor* Target);

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

	// 当前兵种要显示的数据文本
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	FString DisplayStr;

	UPROPERTY()
	class USkillComponent* SkillComponent = nullptr;

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

	// 当前 AI 是否处于攻击状态（同步黑板键值）
	bool M_IsAttack;

// ---------------------------------------- Delegate --------------------------------------
public:
	// 做一些初始化操作
	UPROPERTY(BlueprintAssignable)
	FOnAfterPossessed OnAfterPossessed;

	// 发起攻击
	UPROPERTY(BlueprintAssignable)
	FOnLaunchAttack OnLaunchAttack;

	// 受到攻击
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamage OnTakeDamage;

	// 角色死亡
	UPROPERTY(BlueprintAssignable)
	FOnAIDead OnAIDead;

	// 血量改变
	UPROPERTY(BlueprintAssignable)
	FOnChangeHp OnChangeHp;

// --------------------------------------- Skill -------------------------------------
public:
	// 整个释放技能流程
	UFUNCTION(BlueprintCallable)
	bool RunExecuteSkill(FString SkillId);

	// 判断是否能释放技能
	//UFUNCTION(BlueprintCallable)
	//bool CanExecuteSkill(FString SkillId);

	// 扣除技能消耗
	//UFUNCTION(BlueprintCallable)
	//void ReduceSkillConsume(FString SkillId);
	
	// 执行技能
	//UFUNCTION(BlueprintCallable)
	//void ExecuteSkill(FString SkillId);

	// 获取当前总的 Hp
	UFUNCTION(BlueprintCallable)
	float GetTotalCurrentHp();

	// 获取当前总的 Atk
	UFUNCTION(BlueprintCallable)
	float GetTotalAtk();
};
