// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GeneralDataAsset.h"
#include "UIManager.h"
#include "SkillManager.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

// 用于通知游戏开始运行（点击 GamePlay 按钮之后）
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayGame);	

/**
 * 
 */
UCLASS()
class DEMO1_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();

	UFUNCTION()
	void BeginPlay() override;

	UFUNCTION()
	UGeneralDataAsset* GetGeneralDataAsset();

	UFUNCTION()
	void CreateSkillManager();

	UFUNCTION()
	ASkillManager* GetSkillManager();

	UFUNCTION()
	void PlayGame();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAssets")
	UGeneralDataAsset* GeneralDataAsset = nullptr;

	UPROPERTY()
	FOnPlayGame OnPlayGame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAssets")
	FSoftClassPath SkillManagerClass;

	UPROPERTY()
	ASkillManager* SkillManager = nullptr;
};
