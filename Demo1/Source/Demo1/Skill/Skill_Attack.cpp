// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_Attack.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "Demo1/OtherObjects/Projectile.h"
#include "Kismet/GameplayStatics.h"

void ASkill_Attack::ExecuteSkill(USkillComponent* SkillComponent, TMap<FString, float> FloatMap, TMap<FString, FSoftClassPath> SoftClassPathMap)
{
	if (SkillComponent)
	{
		AAICharacter_Base* AI = Cast<AAICharacter_Base>(SkillComponent->MyOwner);
		if (AI)
		{
			AI->OnLaunchAttack.Broadcast();

			if (FloatMap.Contains("IsHasProjectile") && SoftClassPathMap.Contains("ProjectileClassPath"))
			{
				StartFire(AI, SoftClassPathMap["ProjectileClassPath"]);
			}

			// 记得设置一下释放技能时间
			double CurrentTime = FDateTime::Now().GetTimeOfDay().GetTotalMilliseconds();
			SkillComponent->SetLastReleaseSkillTime(SkillId, CurrentTime);
		}
	}
}

void ASkill_Attack::StartFire(AAICharacter_Base* AI, FSoftClassPath ProjectileClass)
{
	// 创建子弹并发射
	FString ProjectilePath = "Blueprint'";
	ProjectilePath.Append(ProjectileClass.ToString());
	ProjectilePath.Append("'");
	UClass* BP_ProjectileClass = LoadClass<AProjectile>(NULL, *ProjectilePath);

	// 
	FVector SpawnLocation = AI->GetActorLocation() + (AI->GetControlRotation().Vector() * 100.0f) + (AI->GetActorUpVector() * 100.0f);
	FRotator SpawnRotation = AI->GetControlRotation();
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	AProjectile* NewProjectile = Cast<AProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(AI, BP_ProjectileClass, SpawnTransform, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
	if (NewProjectile)
	{
		NewProjectile->SetOwner(AI);
		NewProjectile->Init(AI);
	}
	UGameplayStatics::FinishSpawningActor(NewProjectile, SpawnTransform);
}