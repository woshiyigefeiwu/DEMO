// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillConfig.h"
#include "SkillComponent.generated.h"

class ASkill_Base;

// ÿ�����ܶ�Ӧ��һ��״̬��
USTRUCT(BlueprintType)
struct FSkill_State_Node
{
	GENERATED_BODY()
	
	// ��һ���ͷż��ܵ�ʱ��
	double LastReleaseSkillTime = 0.0f;

	// ���ӵ�Ѫ��
	float AttachHp = 0.0f;

	// ���ӵĹ�����
	float AttachAtk = 0.0f;

	// ÿ�����Կ��Զ�Ӧ�Լ��ĸ���ֵ
	TMap<EAttributeType, float> SkillAttributeValueList;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO1_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// ��ȡ SkillManager
	UFUNCTION()
	class ASkillManager* GetSkillManager();

	// ��ʼ��һ�¼��ܱ�
	UFUNCTION()
	void InitSkillStateList();

	// �ͷ�һ�����ܵ�����
	UFUNCTION()
	bool RunExecuteSkill(FString SkillId);

	// �Ƿ����ͷż���
	UFUNCTION()
	bool CanExecuteSkill(FString SkillId);

	// �۳�����
	UFUNCTION()
	void ReduceSkillConsume(FString SkillId);

	// ������ͷż��ܽӿ�
	UFUNCTION()
	void ExecuteSkill(FString SkillId);

	// ���Դ�����������Ϊ��Ѫ�ļ���
	void TryExecuteSkillWhenHp();

// ---------------------------------- ���Ա���ز��� -----------------------------------------
public:
	// ��ȡ��Ӧ�ļ��ܵĸ���hp����
	//float GetAttachHp(FString SkillId);

	// ���ö�Ӧ���ܵĸ���hp����
	//void SetAttachHp(FString SkillId, float Value);

	// ��ȡ��Ӧ�ļ��ܵĸ���atk����
	//float GetAttachAtk(FString SkillId);

	// ���ö�Ӧ���ܵĸ���atk����
	//void SetAttachAtk(FString SkillId, float Value);

	// ��ȡ�ϴ��ͷż��ܵ�ʱ���
	double GetLastReleaseSkillTime(FString SkillId);

	// �����ϴ��ͷż��ܵ�ʱ���
	void SetLastReleaseSkillTime(FString SkillId, float Value);

	// ��ȡ���м��ܵĸ���hp
	//float GetTotalAttachHp();
	
	// ��ȡ���м��ܵĸ���atk
	//float GetTotalAttachAtk();

	// ---
	float GetSkillAttributeValueByEAttributeType(FString SkillId, EAttributeType AttributeType);

	void SetSkillAttributeValueByEAttributeType(FString SkillId, EAttributeType AttributeType, float Value);

	float GetTotalSkillAttributeValueByEAttributeType(EAttributeType AttributeType);


// -------------------------------------------------------------------------------------
public:	
	// ��ǰ������õļ����б�
	UPROPERTY(EditAnywhere)
	TArray<FString> SkillList;

	// ÿ�����ܶ�Ӧ��һ��״̬
	UPROPERTY()
	TMap<FString, FSkill_State_Node> SkillStateList;

	// ����һ��ÿ�����ܵļ���Ч��ִ����
	UPROPERTY()
	TMap<FString, ASkill_Base*> SkillExecutorCache;

	UPROPERTY()
	AActor* MyOwner;
};
