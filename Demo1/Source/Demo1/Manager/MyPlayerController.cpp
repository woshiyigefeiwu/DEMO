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
	// ���� 3 ��UI
	
	// ��Ϸ��ʼ����
	FString GameStartUIPath = FString(TEXT("Blueprint'/Game/Demo/BluePrints/UI/WBP_GameStart.WBP_GameStart_C'"));
	auto GameStartPathUIClass = LoadClass<UUserWidget>(NULL, *GameStartUIPath);
	if (GameStartPathUIClass != nullptr)
	{
		M_WBP_GameStart = CreateWidget<UUserWidget>(GetWorld(), GameStartPathUIClass);
		M_WBP_Target = M_WBP_GameStart;
	}

	// ѡ����Ӫ����
	FString SelectCampUIPath = FString(TEXT("Blueprint'/Game/Demo/BluePrints/UI/WBP_SelectCamp.WBP_SelectCamp_C'"));
	auto SelectCampUIClass = LoadClass<UUserWidget>(NULL, *SelectCampUIPath);
	if (SelectCampUIClass != nullptr)
	{
		M_WBP_SelectCamp = CreateWidget<UUserWidget>(GetWorld(), SelectCampUIClass);
	}
	
	// ���ý���
	FString PlaceAIUIPath = FString(TEXT("Blueprint'/Game/Demo/BluePrints/UI/WBP_PlaceAI.WBP_PlaceAI_C'"));
	auto PlaceAIUIClass = LoadClass<UUserWidget>(NULL, *PlaceAIUIPath);
	if (PlaceAIUIClass != nullptr)
	{
		M_WBP_PlaceAI = CreateWidget<UUserWidget>(GetWorld(), PlaceAIUIClass);
	}

	// ��Ϸ��ʼ��� UI
	FString GamePlayUIPath = FString(TEXT("Blueprint'/Game/Demo/BluePrints/UI/WBP_GamePlay.WBP_GamePlay_C'"));
	auto GamePlayUIClass = LoadClass<UUserWidget>(NULL, *GamePlayUIPath);
	if (GamePlayUIClass != nullptr)
	{
		M_WBP_GamePlay = CreateWidget<UUserWidget>(GetWorld(), GamePlayUIClass);
	}

	ShowUI();
}

// ��� GameStart UI �ķ��ð�ť
void AMyPlayerController::OnClick_PlaceButton()
{
	RemoveUI();
	SetUI(M_WBP_SelectCamp);
	ShowUI();
}

// ��� GameStart UI �Ŀ�ʼ��Ϸ
void AMyPlayerController::OnClick_GameStart()
{
	RemoveUI();
	SetUI(M_WBP_GamePlay);
	ShowUI();
}

// ��� SelectCamp UI ��ѡ����Ӫ��ť
void AMyPlayerController::OnClick_SelectButton()
{
	RemoveUI();
	SetUI(M_WBP_PlaceAI);
	ShowUI();
}

// ��� SelectCamp UI �ķ��ذ�ť
void AMyPlayerController::OnClick_SelectCampReturn()
{
	RemoveUI();
	SetUI(M_WBP_GameStart);
	ShowUI();
}

// ��� PlaceAI UI �ķ��ذ�ť
void AMyPlayerController::OnClick_PlaceAIReturn()
{
	RemoveUI();
	SetUI(M_WBP_SelectCamp);
	ShowUI();
}

// ��� GamePlay UI4 ����ͣ��ť
void AMyPlayerController::OnClick_PauseButton()
{
	UE_LOG(LogTemp, Error, TEXT("this is AMyPlayerController::OnClick_PauseButton()"));
}

// ��� GamePlay UI4 ���˳���ť
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


