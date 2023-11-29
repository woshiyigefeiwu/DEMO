// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_Attack.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "Demo1/OtherObjects/Projectile.h"
#include "Kismet/GameplayStatics.h"

void ASkill_Attack::ExecuteSkill()
{
	if (SkillComponent)
	{
		AAICharacter_Base* AI = Cast<AAICharacter_Base>(SkillComponent->MyOwner);
		if (AI)
		{
			AI->OnLaunchAttack.Broadcast();

			// 看一下是否有发射物
			FSkill_Config_Effect_Node SkillConfigEffectNode = GetSkillConfigEffectNode();
			if (SkillConfigEffectNode.IsHasProjectile)
			{
				StartFire(AI, SkillConfigEffectNode.ProjectileClassPath);
			}

			// 记得设置一下释放技能时间
			double CurrentTime = FDateTime::Now().GetTimeOfDay().GetTotalMilliseconds();
			SkillComponent->SetLastReleaseSkillTime(SkillId, CurrentTime);
		}
	}
}

FSkill_Config_Effect_Node ASkill_Attack::GetSkillConfigEffectNode()
{
	if (SkillComponent)
	{
		ASkillManager* SkillManager = SkillComponent->GetSkillManager();
		if (SkillManager)
		{
			FSkill_Config_Node SkillConfigNode = SkillManager->GetSkillConfigNode(SkillId);
			return SkillConfigNode.TriggerEffect;
		}
	}
	return FSkill_Config_Effect_Node();
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