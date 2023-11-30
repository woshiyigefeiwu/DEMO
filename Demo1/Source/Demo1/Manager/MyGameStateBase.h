// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GeneralDataAsset.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "UIManager.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAINumChange);			// AI 数量改变的时候抛一个
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverDelegate);

// 当前阵营，当前兵种下的所有AI
USTRUCT(BlueprintType)
struct FCamp_Solider_AIList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int Num;		// 数量

	UPROPERTY()
	TArray<AAICharacter_Base*> Camp_Solider_AIList;
};

// 当前阵营 下所有的 AI
USTRUCT(BlueprintType)
struct FCamp_AIList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int Num;		// 数量

	UPROPERTY()
	TMap<ESoldierType, FCamp_Solider_AIList> Camp_AIList;
};

/**
 * 
 */
UCLASS()
class DEMO1_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void BeginPlay() override;
	
	UFUNCTION()
	void Init();

	UFUNCTION()
	TArray<FCampInfo> GetCampInfoList();

	UFUNCTION(BlueprintCallable)
	TArray<FSoftClassPath> GetSoldierInfoList();

	UFUNCTION(BlueprintCallable)
	void SetCurrentCamp(ECampType CurrentCamp);

	UFUNCTION()
	ECampType GetCurrentCamp();

	UFUNCTION()
	void AddAI(AAICharacter_Base* AI);

	UFUNCTION()
	void DeleteAI(AAICharacter_Base* AI);

	UFUNCTION(BlueprintCallable)
	AUIManager* GetUIManager();

	UFUNCTION()
	void CreateUIManager();

	UFUNCTION()
	UClass* LoadClass_AIBase(FSoftClassPath SoftClassPath);

	UFUNCTION()
	AAICharacter_Base* GetDefaultObject_AIBase(FSoftClassPath SoftClassPath);

	UFUNCTION(BlueprintCallable)
	int GetNumByCampType(ECampType CampType);

	UFUNCTION(BlueprintCallable)
	int GetNumByCampSoliderType(ECampType CampType, ESoldierType SoldierType);

	UFUNCTION(BlueprintCallable)
	ESoldierType GetSoliderType(FSoftClassPath AIClassPath);

	UFUNCTION(BlueprintCallable)
	FString GetDisplayStrBySoliderType(ESoldierType SoldierType);

	// 获取所有同阵营的AI
	UFUNCTION(BlueprintCallable)
	TArray<AAICharacter_Base*> GetFriends(ECampType CampType);

public:
	UPROPERTY()
	FGameOverDelegate GameOverDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnAINumChange OnAINumChange;

private:
	UPROPERTY(EditAnywhere)
	TArray<FCampInfo> M_CampInfoList;

	UPROPERTY(EditAnywhere)
	TArray<FSoftClassPath> M_SoldierInfoList;

	// 当前选择的阵营
	UPROPERTY()
	ECampType M_CurrentCamp;

	// 存游戏里面的所有数据（每个阵营，的每个兵种，的 AI 以及数量）
	UPROPERTY()
	TMap<ECampType, FCamp_AIList> M_AIList;	

	UPROPERTY()
	AUIManager* M_UIManager = nullptr;
};
