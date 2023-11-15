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
	
	// ���� 3 ��UI
	
	// ��Ϸ��ʼ����
	if (GDA)
	{
		M_WBP_GameStart = CreateUI(GDA->WBP_GameStart);
		M_WBP_Target = M_WBP_GameStart;
	}
	
	// ѡ����Ӫ����
	if (GDA)
	{
		M_WBP_SelectCamp = CreateUI(GDA->WBP_SelectCamp);
	}

	// ���ý���
	if (GDA)
	{
		M_WBP_PlaceAI = CreateUI(GDA->WBP_PlaceAI);
	}

	// ��Ϸ��ʼ��� UI
	if (GDA)
	{
		M_WBP_GamePlay = CreateUI(GDA->WBP_GamePlay);
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
	// �� AI ��ӵ� GS ��
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


