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

	UFUNCTION()
	ECampType GetCampType();

	UFUNCTION()
	void SetCampType(ECampType CampType);

	UFUNCTION()
	ESoldierType GetSoldierType();

	UFUNCTION()
	UBehaviorTree* GetBTree();

	UFUNCTION()
	void UpdateWalkSpeed(float Speed);
	
protected:
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

private:
	// ��ǰ����ֵ
	UPROPERTY()
	float M_CurrentHP;

	// �����ĸ���Ӫ
	UPROPERTY()
	ECampType M_CampType;
};
