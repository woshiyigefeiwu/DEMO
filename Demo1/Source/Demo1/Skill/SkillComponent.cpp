// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent.h"
#include "Demo1/Manager/SkillManager.h"
#include "Demo1/Manager/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Skill_Base.h"
#include "Demo1/AICharacter/AICharacter_Base.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}

// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ˫���һ��
	MyOwner = GetOwner();
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(MyOwner);
	AI->SetSkillComponent(this);

	// ��ʼ��һ�¼��ܱ�
	InitSkillStateList();
}

// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ASkillManager* USkillComponent::GetSkillManager()
{
	AMyGameModeBase* GM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(MyOwner));
	if (GM)
	{
		return GM->GetSkillManager();
	}

	return nullptr;
}

void USkillComponent::InitSkillStateList()
{
	ASkillManager* SkillManager = GetSkillManager();

	if (SkillManager)
	{
		for (int i = 0; i < SkillList.Num(); i++)
		{
			if (SkillManager->IsInSkillConfigList(SkillList[i]))		// �Ϸ�����
			{
				FSkill_State_Node SkillState;
				SkillStateList.Add(SkillList[i], SkillState);
			}
		}
	}
}

bool USkillComponent::RunExecuteSkill(FString SkillId)
{
	if (CanExecuteSkill(SkillId))
	{
		ReduceSkillConsume(SkillId);
		ExecuteSkill(SkillId);
		return true;
	}
	return false;
}

bool USkillComponent::CanExecuteSkill(FString SkillId)
{
	ASkillManager* SkillManager = GetSkillManager();
	if (SkillManager)
	{
		// û���� || ���ܱ�����û��
		if (SkillList.Contains(SkillId) == false || SkillManager->IsInSkillConfigList(SkillId) == false)
		{
			return false;
		}

		// ��鴥������
		if (SkillManager->CheckTriggerCondition(SkillId, MyOwner) == false)
		{
			return false;
		}

		// ���CD
		FSkill_Config_Node SkillConfigNode = SkillManager->GetSkillConfigNode(SkillId);
		double SkillCD = SkillConfigNode.OtherConfig.SkillCD * 1000;
		double CurrentTime = FDateTime::Now().GetTimeOfDay().GetTotalMilliseconds();
		double LastTime = GetLastReleaseSkillTime(SkillId);
		if (CurrentTime - LastTime < SkillCD)
		{
			return false;
		}

		//UE_LOG(LogTemp, Error, TEXT("CurrentTime: %f"), CurrentTime);
		//UE_LOG(LogTemp, Error, TEXT("LastTime: %f"), LastTime);
		//UE_LOG(LogTemp, Error, TEXT("CD: %f"), SkillCD);
		//FDateTime tt = FDateTime::Now();
		//int year = tt.GetYear();
		//int month = tt.GetMonth();
		//int day = tt.GetDay();
		//int hour = tt.GetHour();
		//int minute = tt.GetMinute();
		//int second = tt.GetSecond();
		//UE_LOG(LogTemp, Error, TEXT("Time : %d, %d, %d, %d, %d, %d"), year, month, day, hour, minute, second);

		/*
			�������

			������ʱû����Ӧ���Ǽ���������ݲ�ͬ����������ȥ�������жϣ�
			���� ����������ô������ AIManager ȥ������ģ�
			���� ��ң���ô������ ����Manager ȥ������ģ�
		*/
		FString SkillConsumeList = SkillManager->GetSkillConsumeList(SkillId);
	}

	return true;
}

void USkillComponent::ReduceSkillConsume(FString SkillId)
{
	ASkillManager* SkillManager = GetSkillManager();
	if (SkillManager)
	{
		FString SkillConsumeList = SkillManager->GetSkillConsumeList(SkillId);
		/*
			�۳�����

			������ʱû����Ӧ���Ǽ���������ݲ�ͬ����������ȥ�����Ŀ۳���
			���� ����������ô������ AIManager ȥ�۳����ģ�
			���� ��ң���ô������ ����Manager ȥ�۳����ģ�
		*/
	}
}

void USkillComponent::ExecuteSkill(FString SkillId)
{
	ASkill_Base* SkillExecutor = nullptr;

	if (SkillExecutorCache.Contains(SkillId))
	{
		SkillExecutor = SkillExecutorCache[SkillId];
	}
	// û���� �������ô���һ������ִ����
	else
	{
		ASkillManager* SkillManager = GetSkillManager();
		if (SkillManager)
		{
			SkillExecutor = SkillManager->CreateSkillExecutor(SkillId);
			if (SkillExecutor)
			{
				SkillExecutorCache.Add(SkillId, SkillExecutor);
				SkillExecutor->Init(this, SkillId);
			}
		}
	}

	if (SkillExecutor)
	{
		// �ռ�һ������ Map
		TMap<FString,float> FloatMap = CollectFloatConfig(SkillId);
		TMap<FString, FSoftClassPath> SoftClassPathMap = CollectSoftClassPathConfig(SkillId);

		SkillExecutor->ExecuteSkill(this, FloatMap, SoftClassPathMap);
	}
}

void USkillComponent::TryExecuteSkillWhenHp()
{
	ASkillManager* SkillManager = GetSkillManager();
	for (int i = 0; i < SkillList.Num(); i++)
	{
		FSkill_Config_Node SkillConfigNode = SkillManager->GetSkillConfigNode(SkillList[i]);
		if (SkillConfigNode.TriggerCondition.TriggerConditionAttributeValue.Attribute == EAttributeType::HP)
		{
			RunExecuteSkill(SkillList[i]);
		}
	}
}

EAttributeType USkillComponent::GetAttributeType(float Value)
{
	int value = Value;
	EAttributeType Result = EAttributeType::NONE;
	switch (value)
	{
	case 1:
		Result = EAttributeType::HP;
		break;
	case 2:
		Result = EAttributeType::ATK;
		break;
	case 3:
		Result = EAttributeType::AttachHP;
		break;
	case 4:
		Result = EAttributeType::AttachATK;
		break;
	case 5:
		Result = EAttributeType::TotalHp;
		break;
	case 6:
		Result = EAttributeType::TotalAtk;
		break;
	default:
		break;
	}

	return Result;
}

double USkillComponent::GetLastReleaseSkillTime(FString SkillId)
{
	if (SkillStateList.Contains(SkillId))
	{
		return SkillStateList[SkillId].LastReleaseSkillTime;
	}
	return 0.0f;
}

void USkillComponent::SetLastReleaseSkillTime(FString SkillId, float Value)
{
	if (SkillStateList.Contains(SkillId))
	{
		SkillStateList[SkillId].LastReleaseSkillTime = Value;
	}
}

float USkillComponent::GetSkillAttributeValueByEAttributeType(FString SkillId, EAttributeType AttributeType)
{
	if (SkillStateList.Contains(SkillId))
	{
		if (SkillStateList[SkillId].SkillAttributeValueList.Contains(AttributeType) == false)
		{
			SkillStateList[SkillId].SkillAttributeValueList.Add(AttributeType, 0.0f);
		}
		return SkillStateList[SkillId].SkillAttributeValueList[AttributeType];
	}
	return 0.0f;
}

void USkillComponent::SetSkillAttributeValueByEAttributeType(FString SkillId, EAttributeType AttributeType, float Value)
{
	if (SkillStateList.Contains(SkillId))
	{
		if (SkillStateList[SkillId].SkillAttributeValueList.Contains(AttributeType) == false)
		{
			SkillStateList[SkillId].SkillAttributeValueList.Add(AttributeType, 0.0f);
		}
		SkillStateList[SkillId].SkillAttributeValueList[AttributeType] = Value;
	}
}

float USkillComponent::GetTotalSkillAttributeValueByEAttributeType(EAttributeType AttributeType)
{
	float TotalValue = 0.0f;
	for (TMap<FString, FSkill_State_Node>::TConstIterator iter = SkillStateList.CreateConstIterator(); iter; ++iter)
	{
		TotalValue += GetSkillAttributeValueByEAttributeType(iter->Key, AttributeType);
	}

	return TotalValue;
}

TMap<FString, float> USkillComponent::CollectFloatConfig(FString SkillId)
{
	ASkillManager* SkillManager = GetSkillManager();
	FSkill_Config_Node SkillConfig = SkillManager->GetSkillConfigNode(SkillId);
	FSkill_Config_Effect_Node SkillConfigNode = SkillConfig.TriggerEffect;

	TMap<FString, float> ResultMap;

	// �ռ� ��������
	for (TMap<EAttributeType, float>::TConstIterator iter = SkillConfigNode.AdditionalAttributeList.CreateConstIterator(); iter; ++iter)
	{
		UEnum* const CompileModeEnum = StaticEnum<EAttributeType>();
		if (CompileModeEnum)
		{
			// ��һ�� Key������
			FString str = CompileModeEnum->GetDisplayNameTextByValue(static_cast<uint8>(iter->Key)).ToString();
			FString s = "Attribute_";
			s.Append(str);
			ResultMap.Add(s, static_cast<float>(iter->Key));

			// ��һ�� Value������ֵ
			s.Append("_Value");
			ResultMap.Add(s, iter->Value);
		}
	}

	// �ռ�һ�����ö���
	UEnum* const CompileModeEnum = StaticEnum<EActionObject>();
	if(CompileModeEnum)
	{
		FString ActionObjectStr = "Action_Object_";
		FString str = CompileModeEnum->GetDisplayNameTextByValue(static_cast<uint8>(SkillConfig.OtherConfig.ActionObject)).ToString();
		ActionObjectStr.Append(str);
		ResultMap.Add(ActionObjectStr, static_cast<float>(SkillConfig.OtherConfig.ActionObject));
	}

	// �ռ� �������Ƿ��з����
	FString s = "IsHasProjectile";
	ResultMap.Add(s, SkillConfigNode.IsHasProjectile);

	return ResultMap;
}

TMap<FString, FSoftClassPath> USkillComponent::CollectSoftClassPathConfig(FString SkillId)
{
	ASkillManager* SkillManager = GetSkillManager();
	FSkill_Config_Effect_Node SkillConfigNode = SkillManager->GetSkillConfigNode(SkillId).TriggerEffect;
	TMap<FString, FSoftClassPath> ResultMap;

	FString s = "ProjectileClassPath";
	ResultMap.Add(s, SkillConfigNode.ProjectileClassPath);

	return ResultMap;
}
