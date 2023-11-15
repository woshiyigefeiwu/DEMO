// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "MyGameStateBase.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;

	bReplicates = true;
}

void AMyPlayerController::BeginPlay()
{
	//GetWorldTimerManager().SetTimer(M_TimerHandle, this, &AMyPlayerController::HideMouse, 5.0f, false);

	// why ?
	//if (GetLocalRole() == ROLE_AutonomousProxy)
	//{
		LoadUI();
	//}
}

void AMyPlayerController::LoadUI()
{
	AMyGameModeBase* GM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	UGeneralDataAsset* GDA = nullptr;
	if (GM)
	{
		GDA = GM->GeneralDataAsset;
	}
	
	// 创建 3 个UI
	
	// 游戏开始界面
	if (GDA)
	{
		M_WBP_GameStart = CreateUI(GDA->WBP_GameStart);
		M_WBP_Target = M_WBP_GameStart;
	}
	
	// 选择阵营界面
	if (GDA)
	{
		M_WBP_SelectCamp = CreateUI(GDA->WBP_SelectCamp);
	}

	// 放置界面
	if (GDA)
	{
		M_WBP_PlaceAI = CreateUI(GDA->WBP_PlaceAI);
	}

	// 游戏开始后的 UI
	if (GDA)
	{
		M_WBP_GamePlay = CreateUI(GDA->WBP_GamePlay);
	}

	ShowUI();
}

// 点击 GameStart UI 的放置按钮
void AMyPlayerController::OnClick_PlaceButton()
{
	RemoveUI();
	SetUI(M_WBP_SelectCamp);
	ShowUI();
}

// 点击 GameStart UI 的开始游戏
void AMyPlayerController::OnClick_GameStart()
{
	RemoveUI();
	SetUI(M_WBP_GamePlay);
	ShowUI();
}

// 点击 SelectCamp UI 的选择阵营按钮
void AMyPlayerController::OnClick_SelectButton()
{
	RemoveUI();
	SetUI(M_WBP_PlaceAI);
	ShowUI();
}

// 点击 SelectCamp UI 的返回按钮
void AMyPlayerController::OnClick_SelectCampReturn()
{
	RemoveUI();
	SetUI(M_WBP_GameStart);
	ShowUI();
}

// 点击 PlaceAI UI 的返回按钮
void AMyPlayerController::OnClick_PlaceAIReturn()
{
	RemoveUI();
	SetUI(M_WBP_SelectCamp);
	ShowUI();
}

// 点击 GamePlay UI4 的暂停按钮
void AMyPlayerController::OnClick_PauseButton()
{
	UE_LOG(LogTemp, Error, TEXT("this is AMyPlayerController::OnClick_PauseButton()"));
}

// 点击 GamePlay UI4 的退出按钮
void AMyPlayerController::OnClick_ExitButton()
{
	RemoveUI();
	SetUI(M_WBP_GameStart);
	ShowUI();
}

void AMyPlayerController::SetUI(UUserWidget* TargetUI)
{
	M_WBP_Target = TargetUI;
}

void AMyPlayerController::ShowUI()
{
	if (M_WBP_Target)
	{
		M_WBP_Target->AddToViewport();
	}
}

void AMyPlayerController::RemoveUI()
{
	if (M_WBP_Target)
	{
		M_WBP_Target->RemoveFromParent();
	}
}

UUserWidget* AMyPlayerController::CreateUI(FSoftClassPath SoftClassPath)
{
	FString UIPath = "Blueprint'";
	UIPath.Append(SoftClassPath.ToString());
	UIPath.Append("'");
	UClass* UIClass = LoadClass<UUserWidget>(NULL, *UIPath);
	UUserWidget* UI = CreateWidget<UUserWidget>(GetWorld(), UIClass);
	return UI;
}


void AMyPlayerController::SpawnAI(FSoftClassPath SoftClassPath, FVector MouseLocation)
{
	UClass* AIClass = LoadAIClass(SoftClassPath);
	AAICharacter_Base* AI = GetWorld()->SpawnActor<AAICharacter_Base>(AIClass, FTransform(MouseLocation));
	
	AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	// 将 AI 添加到 GS 中
	if (AI && GS)
	{
		AI->SetCampType(GS->GetCurrentCamp());
		GS->AddAI(AI);
	}
}

UClass* AMyPlayerController::LoadAIClass(FSoftClassPath SoftClassPath)
{
	FString AIPath = "Blueprint'";
	AIPath.Append(SoftClassPath.ToString());
	AIPath.Append("'");
	UClass* AIClass = LoadClass<AActor>(NULL, *AIPath);
	return AIClass;
}

//void AMyPlayerController::HideMouse()
//{
//	bShowMouseCursor = false;
//}


