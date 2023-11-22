// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "MyGameModeBase.h"
#include "MyGameStateBase.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AUIManager::AUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUIManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ��ʼ��һ��UI���ã��Լ�һЩ�����߼�
void AUIManager::Init()
{
	// ��ʼ��һ������
	AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM && GM->GeneralDataAsset)
	{
		M_UIMap = GM->GeneralDataAsset->UIMap;

		// ����Ĭ�� UI
		ShowUI(GM->GeneralDataAsset->DefaultUI);
	}

	// ��һ����Ϸ����
	AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	if (GS)
	{
		GS->GameOverDelegate.AddDynamic(this, &AUIManager::OnGameOver);
	}
}

void AUIManager::SetUI(FString UIName)
{
	if (M_UICache.Contains(UIName))
	{
		M_CurrentUI = M_UICache[UIName];
	}
}

void AUIManager::RemoveUI()
{
	if (M_CurrentUI)
	{
		M_CurrentUI->RemoveFromParent();
	}
}

void AUIManager::ShowUI(FString UIName)
{
	// �������ñ�
	if (M_UIMap.Contains(UIName) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("This UI Is Not Configed"));
		return ;
	}

	// û�� UI �ٴ���
	if (M_UICache.Contains(UIName) == false || M_UICache[UIName] == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("This UI Is Not Create."));

		M_UICache.Add(UIName, CreateUI(UIName));
	}

	RemoveUI();
	SetUI(UIName);

	if (M_CurrentUI)
	{
		M_CurrentUI->AddToViewport();
	}
}

UUserWidget* AUIManager::CreateUI(FString UIName)
{
	FString UIPath = "Blueprint'";
	UIPath.Append(M_UIMap[UIName].ToString());
	UIPath.Append("'");
	UClass* UIClass = LoadClass<UUserWidget>(NULL, *UIPath);

	UUserWidget* UI = nullptr;
	if (UIClass)
	{
		UI = CreateWidget<UUserWidget>(GetWorld(), UIClass);
	}
	
	return UI;
}

void AUIManager::OnGameOver()
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::Printf(TEXT("this is OnGameOver()")));

	ShowUI("UI_GameOver");
}
