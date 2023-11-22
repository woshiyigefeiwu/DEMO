// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

// 用于管理 UI，看看能不能设计成一个全局单例...

UCLASS()
class DEMO1_API AUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUIManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	
	UFUNCTION()
	void Init();
	
	// 设置 UI
	UFUNCTION()
	void SetUI(FString UIName);

	// 移除 UI
	UFUNCTION()
	void RemoveUI();

	// 显示 UI
	UFUNCTION(BlueprintCallable)
	void ShowUI(FString UIName);

	// 创建 UI
	UFUNCTION(BlueprintCallable)
	UUserWidget* CreateUI(FString UIName);

	// 一些逻辑
	UFUNCTION()
	void OnGameOver();

private:
	// UI 的总配置，从DataAsset中获取，在Init()进行初始化
	UPROPERTY()
	TMap<FString, FSoftClassPath> M_UIMap;

	// 缓存一些创建过的UI
	UPROPERTY()
	TMap<FString, UUserWidget*> M_UICache;

	// 当前正在显示的 UI
	UPROPERTY()
	UUserWidget* M_CurrentUI = nullptr;
};
