// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Demo1/Manager/GeneralDataAsset.h"
#include "BehaviorTree/BehaviorTree.h"

#include "CoreMinimal.h"
#include "Demo1/Demo1Character.h"
#include "AICharacter_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLaunchAttack);		// ���𹥻�
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindTargetFinish);	// ���� Target ֮��

UCLASS()
class DEMO1_API AAICharacter_Base : public ADemo1Character
{
	GENERATED_BODY()
	
public:
	AAICharacter_Base();

	void Tick(float DeltaSeconds) override;

// ----------------------------------------- Init��Get��Set��Check ���� ----------------------------------------------
public:
	// ��ʼ��һЩ AI ������
	UFUNCTION()
	virtual void Init();

	// ��ȡ��ǰ AI ����Ӫ����
	UFUNCTION()
	ECampType GetCampType();

	// ���� AI ����Ӫ����
	UFUNCTION()
	void SetCampType(ECampType CampType);

	// ��ȡ��ǰ AI ����ʲô����
	UFUNCTION()
	ESoldierType GetSoldierType();

	// ��ȡһ�µ�ǰ AI ִ�е���Ϊ��
	UFUNCTION()
	UBehaviorTree* GetBTree();

	// �ж��Ƿ��ڹ���״̬
	UFUNCTION()
	bool IsAttack();

	// �ж��Ƿ�����
	UFUNCTION()
	bool IsDead();

	// ����һ�µ�ǰ HP
	UFUNCTION()
	float SetCurrentHP(float NewHP);

	// ��ȡ��ǰ AI ��Ŀ�����
	AAICharacter_Base* GetTargetEnemy();

	// ���õ�ǰ AI ��Ŀ�����
	void SetTargetEnemy(AAICharacter_Base* NewEnemy);

	// ��ȡ Enemy ����
	TArray<AAICharacter_Base*> GetEnemyArray();

// ------------------------------------------- �������� -----------------------------------
public:
	// ����һ�� AI �������ٶ�
	UFUNCTION(BlueprintCallable)
	void UpdateWalkSpeed();

	// �ܵ���������APawn���ǣ�
	UFUNCTION()
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// ѡ�У�����ѡ�й�����ò�ͬ��ѡ�з�ʽ��
	UFUNCTION()
	AAICharacter_Base* SelectTarget();

	// �ҵ�һ�����ֵĵ��ˣ���������Լ���д��
	virtual AAICharacter_Base* SelectTarget_First();

	// �Ҿ�������ĵ��ˣ���������Լ���д��
	virtual AAICharacter_Base* SelectTarget_Nearest();

	// AI ������Ĵ���
	UFUNCTION()
	void AIDead();

	// ��ն�ʱ��
	UFUNCTION()
	void ClearTimerHandle();

	// �Ƿ�����CD��
	UFUNCTION(BlueprintCallable)
	bool IsInAttackCD();

	// ���Ŀ��ľ���
	UFUNCTION(BlueprintCallable)
	float GetDistanceFromEnemy();

// ---------------------------------------- AI Behavior �ӿڣ�BT ���ã� ------------------------------------------------
public:
	// ���𹥻�����������дһ�£�
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	virtual void AttackEnemy();

	// Ѱ�ҵ���
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	virtual void FindTarget();

	// ���빥�� CD
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	void EntryAttackCD();

	// ʩ���˺�
	UFUNCTION(BlueprintCallable)
	void AI_ApplyDamage();

// ----------------------------------------- AI �Ļ������� --------------------------------------------
public:
	// �������ֵ
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float MaxHP;

	// ������
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float Atk;

	// ���� CD
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float AtkCD;

	// �ƶ��ٶ�
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float MoveSpeed;

	// ��ײ���
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	FVector CollisionVolume;

	// ��ʾ��ͼƬ
	UPROPERTY(EditAnywhere, Category = "BaseConfig", meta = (AllowedClasses = "Texture"))
	FSoftObjectPath ShowImage;

	// ��ת�ٶ�
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float RotateSpeed;

	// ������ʽ��ֱ�ӷ�����������У�

	// ��ǰ���ֵ�����
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	ESoldierType SoldierType;

	// ��ǰ AI ʹ�õ���Ϊ��
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	UBehaviorTree* BTree = nullptr;

	// ѡ�й���
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	EEnemySelectRule EnemySelectRule;

	// ��֪�뾶�����ֵ��˵ķ�Χ������׷����
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float PerceptionRadius;

	// �뿪��֪�İ뾶
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float LosePerceptionRadius;
	
	// ������Χ��׷�����˵��˷�Χ�ڵ�ʱ��ͷ��𹥻���
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float AttackRadius;

protected:
	// ��ǰ����ֵ
	UPROPERTY()
	float M_CurrentHP;

	// �����ĸ���Ӫ
	UPROPERTY()
	ECampType M_CampType;

	// �Ƿ���������״̬
	UPROPERTY()
	bool M_IsDead = false;
	
// --------------------------------------- AI ��ص����� ----------------------------------
private:
	// ��ʱ�������ڴ�����CD
	UPROPERTY()
	FTimerHandle M_TimerHandle;

	// ��ǰ AI �� Ŀ����ˣ�ͬ���ڰ��ֵ��
	UPROPERTY()
	AAICharacter_Base* M_TargetEnemy = nullptr;

	// ��ǰ AI �Ƿ��ڹ���״̬��ͬ���ڰ��ֵ��
	bool M_IsAttack;

public:
	// ��⵽�ĵ���
	UPROPERTY()
	TArray<AAICharacter_Base*> EnemyArray;

// ---------------------------------------- Delegate --------------------------------------
public:
	// Ѱ����Ŀ��֮���׸��¼�
	UPROPERTY()
	FOnFindTargetFinish OnFindTargetFinish;

	// ���𹥻�
	UPROPERTY(BlueprintAssignable)
	FOnLaunchAttack OnLaunchAttack;
};
