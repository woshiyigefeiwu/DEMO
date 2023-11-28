// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillConfig.h"
#include "SkillComponent.generated.h"

class ASkill_Base;




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

	void CreateSkill();

	// ������ͷż��ܽӿ�
	void ExecuteSkill(ESkillType SkillType);

	// �Ƿ����ͷż���
	UFUNCTION(BlueprintCallable)
	bool CanExecuteSkill(ESkillType SkillType);

public:	
	// ��ǰ������õļ����б�
	UPROPERTY(EditAnywhere)
	TMap<ESkillType, FArrayString_Node> SkillConfig;
	
	// ��ǰ����ļ����߼�
	UPROPERTY()
	TMap<ESkillType, ASkill_Base*> Skills;

public:
	UPROPERTY()
	AActor* MyOwner;

	
};
