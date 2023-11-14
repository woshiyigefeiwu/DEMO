// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralConfig.h"

// Sets default values
AGeneralConfig::AGeneralConfig()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeneralConfig::BeginPlay()
{
	Super::BeginPlay();
	
}

// 把数据导到 GameState 里面一下
void AGeneralConfig::Init()
{

}

// Called every frame
void AGeneralConfig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

