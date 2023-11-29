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
	virtual void Init(class USkillComponent* NewSkillComponent, FString SkillId);

	// ����ִ��
	virtual void ExecuteSkill(){}

public:	
	// ��ǰ����Ч��ִ�������ĸ������������
	class USkillComponent* SkillComponent = nullptr;

	// ��ǰ����Ч��ִ���������ĸ����ܣ������޸����Ա�
	FString SkillId;
};
