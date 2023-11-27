// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Demo1/Manager/SkillManager.h"
#include "Skill_Base.generated.h"

UCLASS()
class DEMO1_API ASkill_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_Base();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ��ʼ��
	virtual void Init(class USkillComponent* NewSkillComponent);

// ------------------------ Skill Function----------------------------

	// �ͷŵ�ǰ�ļ���
	virtual void ReleaseSkill();

	// �ж��Ƿ����ͷż���
	virtual bool CanReleaseSkill(){return false;}

	// �۳�����
	virtual void ReduceConsume(){}

	// ����ִ��
	virtual void ExecuteSkill(){}

// ------------------------ Skill Property----------------------------
public:	
	// ��ǰ���ܶ������ĸ������������
	class USkillComponent* SkillComponent;


public:
	// ������������
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerCondition")
	ETriggerCondition TriggerCondition;

	// ������������
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerConsume")
	ETriggerConsume TriggerConsume;

	// ���ö���
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|ActionObject")
	EActionObject ActionObject;

	// ��ǰ���ܵ����ͣ����ⲿ��һ��ֵ��
	//UPROPERTY(BlueprintReadOnly, Category = "SkilleConfig")
	//ESkillType SkillType;
};
