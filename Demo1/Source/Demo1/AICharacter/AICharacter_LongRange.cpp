// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter_LongRange.h"
#include "Demo1/AIController/AIController_Base.h"
#include "Demo1/OtherObjects/Projectile.h"
#include "Kismet/GameplayStatics.h"

void AAICharacter_LongRange::BeginPlay()
{
	Super::BeginPlay();
}

void AAICharacter_LongRange::AttackEnemy(AAICharacter_Base* Enemy)
{
	UE_LOG(LogTemp, Error, TEXT("this is AAICharacter_LongRange::AttackEnemy()"));

	// ��ͼ�Ǳ߰󶨣���ʼ����������
	OnLaunchAttack.Broadcast();

	// ����
	StartFire();
}

void AAICharacter_LongRange::StartFire()
{
	// �����ӵ�������
	FString ProjectilePath = "Blueprint'";
	ProjectilePath.Append(ProjectileClass.ToString());
	ProjectilePath.Append("'");
	UClass* BP_ProjectileClass = LoadClass<AProjectile>(NULL, *ProjectilePath);

	// 
	FVector SpawnLocation = GetActorLocation() + (GetControlRotation().Vector() * 100.0f) + (GetActorUpVector() * 100.0f);
	FRotator SpawnRotation = GetControlRotation();
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	AProjectile* NewProjectile = Cast<AProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, BP_ProjectileClass, SpawnTransform, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
	if (NewProjectile)
	{
		NewProjectile->SetOwner(this);
		NewProjectile->Init(this);
	}
	UGameplayStatics::FinishSpawningActor(NewProjectile, SpawnTransform);
}
