// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "MyGameStateBase.h"
#include "UIManager.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;

	bReplicates = true;
}

void AMyPlayerController::BeginPlay()
{
	//GetWorldTimerManager().SetTimer(M_TimerHandle, this, &AMyPlayerController::HideMouse, 5.0f, false);

	Init();
}

void AMyPlayerController::Init()
{	

}

void AMyPlayerController::SpawnAI(FSoftClassPath SoftClassPath, FVector MouseLocation)
{
	UClass* AIClass = LoadAIClass(SoftClassPath);
	AAICharacter_Base* AI = GetWorld()->SpawnActor<AAICharacter_Base>(AIClass, FTransform(MouseLocation));
	
	AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	// 将 AI 添加到 GS 中
	if (AI && GS)
	{
		//AI->SetCampType(GS->GetCurrentCamp());
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


