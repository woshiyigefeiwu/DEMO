// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"

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
	// 创建 3 个UI
	
	// 游戏开始界面
	FString GameStartUIPath = FString(TEXT("Blueprint'/Game/Demo/BluePrints/UI/WBP_GameStart.WBP_GameStart_C'"));
	auto GameStartPathUIClass = LoadClass<UUserWidget>(NULL, *GameStartUIPath);
	if (GameStartPathUIClass != nullptr)
	{
		M_WBP_GameStart = CreateWidget<UUserWidget>(GetWorld(), GameStartPathUIClass);
		M_WBP_Target = M_WBP_GameStart;
	}

	// 选择阵营界面
	FString SelectCampUIPath = FString(TEXT("Blueprint'/Game/Demo/BluePrints/UI/WBP_SelectCamp.WBP_SelectCamp_C'"));
	auto SelectCampUIClass = LoadClass<UUserWidget>(NULL, *SelectCampUIPath);
	if (SelectCampUIClass != nullptr)
	{
		M_WBP_SelectCamp = CreateWidget<UUserWidget>(GetWorld(), SelectCampUIClass);
	}
	
	// 放置界面
	FString PlaceAIUIPath = FString(TEXT("Blueprint'/Game/Demo/BluePrints/UI/WBP_PlaceAI.WBP_PlaceAI_C'"));
	auto PlaceAIUIClass = LoadClass<UUserWidget>(NULL, *PlaceAIUIPath);
	if (PlaceAIUIClass != nullptr)
	{
		M_WBP_PlaceAI = CreateWidget<UUserWidget>(GetWorld(), PlaceAIUIClass);
	}

	// 游戏开始后的 UI
	FString GamePlayUIPath = FString(TEXT("Blueprint'/Game/Demo/BluePrints/UI/WBP_GamePlay.WBP_GamePlay_C'"));
	auto GamePlayUIClass = LoadClass<UUserWidget>(NULL, *GamePlayUIPath);
	if (GamePlayUIClass != nullptr)
	{
		M_WBP_GamePlay = CreateWidget<UUserWidget>(GetWorld(), GamePlayUIClass);
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

UClass* AMyPlayerController::LoadMyClass(FSoftClassPath SoftClassPath)
{
	//FString AIPath = "Blueprint'";
	//AIPath.Append(SoftClassPath.ToString());
	////AIPath.Append("_C'");
	//UClass* AIClass = LoadClass<AMyProject02Character>(NULL, *AIPath);

	return nullptr;
}

//void AMyPlayerController::HideMouse()
//{
//	bShowMouseCursor = false;
//}


