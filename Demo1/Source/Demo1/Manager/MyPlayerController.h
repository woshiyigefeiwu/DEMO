// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	UFUNCTION()
	void BeginPlay() override;

	// ---------------------------- UI -------------------------

	UFUNCTION()
	void LoadUI();

	// M_WBP_GameStart ��������ť�л�
	UFUNCTION(BlueprintCallable)
	void OnClick_PlaceButton();

	UFUNCTION(BlueprintCallable)
	void OnClick_GameStart();

	// M_WBP_SelectCamp �������л�
	UFUNCTION(BlueprintCallable)
	void OnClick_SelectButton();

	UFUNCTION(BlueprintCallable)
	void OnClick_SelectCampReturn();

	// M_WBP_PlaceAI ��һ���л�
	UFUNCTION(BlueprintCallable)
	void OnClick_PlaceAIReturn();

	// M_WBP_GamePlay �������л�s
	UFUNCTION()
	void OnClick_PauseButton();

	UFUNCTION()
	void OnClick_ExitButton();

	// ���� UI
	UFUNCTION()
	void SetUI(UUserWidget* TargetUI);

	// ��ʾ UI
	UFUNCTION()
	void ShowUI();

	// �Ƴ� UI
	UFUNCTION()
	void RemoveUI();

	UFUNCTION(BlueprintCallable)
	void RemoveAllUI();

	UFUNCTION()
	UUserWidget* CreateUI(FSoftClassPath SoftClassPath);

	

	
	// ------------------------------------------ spawn AI -----------------------------------------

	UFUNCTION(BlueprintCallable)
	void SpawnAI(FSoftClassPath SoftClassPath, FVector MouseLocation);

	UFUNCTION()
	UClass* LoadAIClass(FSoftClassPath SoftClassPath);

	// ------------------------------------------ other --------------------------------------------

	//UFUNCTION()
	//void HideMouse();

private:
	//UPROPERTY()
	//FTimerHandle M_TimerHandle;

	// ��ǰ����ʾ��UI���ĸ�
	UPROPERTY()
	UUserWidget* M_WBP_Target = nullptr;

	UPROPERTY()
	UUserWidget* M_WBP_GameStart = nullptr;

	UPROPERTY()
	UUserWidget* M_WBP_PlaceAI = nullptr;

	UPROPERTY()
	UUserWidget* M_WBP_SelectCamp = nullptr;

	UPROPERTY()
	UUserWidget* M_WBP_GamePlay = nullptr;
};
