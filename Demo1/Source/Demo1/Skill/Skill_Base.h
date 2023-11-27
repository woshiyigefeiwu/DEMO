// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillComponent.h"
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

public:	
	// ��ǰ���ܶ������ĸ������������
	class USkillComponent* SkillComponent;


// ----------------------------------- �Ȳ���һ�� --------------------------------
public:
	// ��ǰ���ܵ����ͣ����ⲿ��һ��ֵ��
	UPROPERTY(EditAnywhere, Category = "SkilleConfig", meta = (DisplayName = "��������"))
	ESkillType SkillType;

	// ��������
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerCondition", meta = (DisplayName = "��������"))
	ETriggerCondition TriggerCondition;

	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerCondition", meta = (EditCondition = "TriggerCondition == ETriggerCondition::LessThan", EditConditionHides, DisplayName = "������ֵ����"))
	FAttributeValue AttributeValue;


	// ��������
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerConsume", meta = (DisplayName = "��������"))
	TMap<ETriggerConsume,float> TriggerConsume;


	// ���ö���
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|ActionObject", meta = (DisplayName = "���ö���"))
	EActionObject ActionObject;


	// ����Ч�������Ը���ֵ��
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|AttributeEffectList", meta = (EditCondition = "SkillType == ESkillType::ChangeAttributeValue", EditConditionHides, DisplayName = "���Ը���ֵ"))
	TMap<EAttribute, float> AttributeEffectList;
};
