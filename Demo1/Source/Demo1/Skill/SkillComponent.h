// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	void ReleaseSkill(FString SkillId);

public:	
	// ��ǰ������õļ����б�
	UPROPERTY(EditAnywhere)
	TArray<FString> SkillConfig;

	// ��ǰ����ļ���
	UPROPERTY()
	TMap<FString, ASkill_Base*> Skills;

private:
	UPROPERTY()
	AActor* Owner;

	
};
