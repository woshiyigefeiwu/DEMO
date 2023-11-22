// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

// ���ڹ��� UI�������ܲ�����Ƴ�һ��ȫ�ֵ���...

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
	
	// ���� UI
	UFUNCTION()
	void SetUI(FString UIName);

	// �Ƴ� UI
	UFUNCTION()
	void RemoveUI();

	// ��ʾ UI
	UFUNCTION(BlueprintCallable)
	void ShowUI(FString UIName);

	// ���� UI
	UFUNCTION(BlueprintCallable)
	UUserWidget* CreateUI(FString UIName);

	// һЩ�߼�
	UFUNCTION()
	void OnGameOver();

private:
	// UI �������ã���DataAsset�л�ȡ����Init()���г�ʼ��
	UPROPERTY()
	TMap<FString, FSoftClassPath> M_UIMap;

	// ����һЩ��������UI
	UPROPERTY()
	TMap<FString, UUserWidget*> M_UICache;

	// ��ǰ������ʾ�� UI
	UPROPERTY()
	UUserWidget* M_CurrentUI = nullptr;
};
