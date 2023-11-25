// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Demo1/Manager/GeneralDataAsset.h"
#include "BehaviorTree/BehaviorTree.h"

#include "CoreMinimal.h"
#include "Demo1/Demo1Character.h"
#include "AICharacter_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAfterPossessed);		//
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLaunchAttack);		// ���𹥻�
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeDamage);			// �ܵ��˺���ˢһ�� UI �ȵȣ�
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAIDead);			// ��ɫ����

UCLASS()
class DEMO1_API AAICharacter_Base : public ADemo1Character
{
	GENERATED_BODY()
	
public:
	AAICharacter_Base();

	void Tick(float DeltaSeconds) override;

	void BeginPlay() override;

// ----------------------------------------- Init��Get��Set��Check ���� ----------------------------------------------
public:
	// ��ʼ��һЩ AI �����ԣ�ʱ����AIC OnPossess ʱ��
	UFUNCTION()
	virtual void Init();

	// ��ͼ��д���ṩ����ͼȥ��ʼ��һЩ������ʱ����BeginPlay��
	UFUNCTION(BlueprintImplementableEvent)
	void Init_BP();

	// ��ȡ��ǰ AI ����Ӫ����
	UFUNCTION()
	ECampType GetCampType();

	// ��ȡ��ǰ��Ӫ��Ӧ����ɫ
	UFUNCTION(BlueprintCallable)
	FColor GetColorByCampType();

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

	// ��ȡ������
	UFUNCTION()
	float GetAtk();

	// ��ȡ�������ֵ
	UFUNCTION(BlueprintCallable)
	float GetMaxHp() { return MaxHP; }

	// ��ȡ��ǰ����ֵ
	UFUNCTION(BlueprintCallable)
	float GetCurrentHp() { return M_CurrentHP; }

	// ����һ�µ�ǰ HP
	UFUNCTION()
	float SetCurrentHP(float NewHP);

	// ��ȡ��ʾ��ͼƬ
	UFUNCTION(BlueprintCallable)
	FString GetImagePath();

// ------------------------------------------- �������� -----------------------------------
public:
	// ����һ�� AI �������ٶ�
	UFUNCTION(BlueprintCallable)
	void UpdateWalkSpeed();

	// �ܵ���������APawn���ǣ�
	UFUNCTION()
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// AI ������Ĵ���
	UFUNCTION()
	void AIDead();

	// ��ն�ʱ��
	UFUNCTION()
	void ClearTimerHandle();

	// �Ƿ�����CD��
	UFUNCTION(BlueprintCallable)
	bool IsInAttackCD();

// ---------------------------------------- AI Behavior �ӿڣ�BT ���ã� ------------------------------------------------
public:
	// ���𹥻�����������дһ�£�
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	virtual void AttackEnemy(AAICharacter_Base* Enemy);

	// Ѱ�ҵ���
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	virtual void FindTarget();

	// ���빥�� CD
	UFUNCTION(BlueprintCallable, Category = "Base_AI_Behavior")
	void EntryAttackCD();

	// ʩ���˺�
	UFUNCTION(BlueprintCallable)
	void AI_ApplyDamage(AAICharacter_Base* Enemy);

// ----------------------------------------- AI �Ļ������� --------------------------------------------
public:
	// ��ʾѪ��
	//UPROPERTY(EditAnywhere, Category = WidgetComponent)
	//class UWidgetComponent* WidgetComponent;

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

	// ��ǰ AI �Ƿ��ڹ���״̬��ͬ���ڰ��ֵ��
	bool M_IsAttack;

// ---------------------------------------- Delegate --------------------------------------
public:
	// ��һЩ��ʼ������
	UPROPERTY(BlueprintAssignable)
	FOnAfterPossessed OnAfterPossessed;

	// ���𹥻�
	UPROPERTY(BlueprintAssignable)
	FOnLaunchAttack OnLaunchAttack;

	// �ܵ�����
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamage OnTakeDamage;

	// ��ɫ����
	UPROPERTY(BlueprintAssignable)
	FOnAIDead OnAIDead;
};
