// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_DeadExplosion.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "Demo1/OtherObjects/ExplosionObject.h"
#include "Kismet/GameplayStatics.h"

void ASkill_DeadExplosion::ExecuteSkill(USkillComponent* SkillComponent, TMap<FString, float> FloatMap, TMap<FString, FSoftClassPath> SoftClassPathMap)
{
	if (SkillComponent)
	{
		AAICharacter_Base* AI = Cast<AAICharacter_Base>(SkillComponent->MyOwner);
		if (AI)
		{
			FString ExplosionClassPathStr = "Skill_DeadExplosion_ExplosionClassPath";
			if (SoftClassPathMap.Contains(ExplosionClassPathStr))
			{
				float AfterExplosionTime = 0;
				FVector ExplosionRange = FVector();

				CreateExplosionObject(AI, SoftClassPathMap[ExplosionClassPathStr], AfterExplosionTime, ExplosionRange);
			}

			// 记得设置一下释放技能时间
			double CurrentTime = FDateTime::Now().GetTimeOfDay().GetTotalMilliseconds();
			SkillComponent->SetLastReleaseSkillTime(SkillId, CurrentTime);
		}
	}
}

void ASkill_DeadExplosion::CreateExplosionObject(AAICharacter_Base* AI, FSoftClassPath ExplosionSoftClassPath, float AfterExplosionTime, FVector ExplosionRange)
{
	FString ExplosionObjectPath = "Blueprint'";
	ExplosionObjectPath.Append(ExplosionSoftClassPath.ToString());
	ExplosionObjectPath.Append("'");
	UClass* BP_ProjectileClass = LoadClass<AExplosionObject>(NULL, *ExplosionObjectPath);

	FVector SpawnLocation = AI->GetActorLocation();
	FRotator SpawnRotation = AI->GetControlRotation();
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	AExplosionObject* NewProjectile = Cast<AExplosionObject>(UGameplayStatics::BeginDeferredActorSpawnFromClass(AI, BP_ProjectileClass, SpawnTransform, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
	if (NewProjectile)
	{
		NewProjectile->SetOwner(AI);
		NewProjectile->Init(AI, ExplosionRange, AfterExplosionTime);
	}
	UGameplayStatics::FinishSpawningActor(NewProjectile, SpawnTransform);
}
