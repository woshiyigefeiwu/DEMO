// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Demo1/Skill/SkillConfig.h"
#include "SkillManager.generated.h"

class ASkill_Base;
class AAICharacter_Base;

UCLASS()
class DEMO1_API ASkillManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// ������
	UFUNCTION()
	UClass* LoadSkillExecutorClass(FSoftClassPath SoftClassPath);

	// ��������ִ����
	UFUNCTION()
	ASkill_Base* CreateSkillExecutor(FString SkillId);

	// ��ȡ����
	UFUNCTION()
	USkillConfig* GetSkillConfig();

	// �ж� Skill �Ƿ������ñ���
	UFUNCTION()
	bool IsInSkillConfigList(FString SkillId);

	// ���ݼ���Id��ȡ���������
	UFUNCTION()
	FSkill_Config_Node GetSkillConfigNode(FString SkillId);

	// ���������������ã������������б�
	UFUNCTION()
	FString GetSkillConsumeList(FString SkillId);


	// -------------------------------- �������� -------------------------------
	// ���ݴ��������в�ͬ���������ͻ�ȡһ��ֵ
	float GetValueByAttributeType(EAttributeType AttributeType, AAICharacter_Base* AI);

	// ��鴥�������Ƿ�����
	UFUNCTION()
	bool CheckTriggerCondition(FString SkillId, AActor* Actor);

	// ������������Ϊ LessThan �ľ����ж��߼���������һ�����������ڵ㣩
	bool CheckTriggerCondition_LessThan(FSkill_Config_Condition_Node TriggerCondition, AActor* Actor);

	// ������������Ϊ GreaterThan �ľ����ж��߼���������һ�����������ڵ㣩
	bool CheckTriggerCondition_GreaterThan(FSkill_Config_Condition_Node TriggerCondition, AActor* Actor);
};
