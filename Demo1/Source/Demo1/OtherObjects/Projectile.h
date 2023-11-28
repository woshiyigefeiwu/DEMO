// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Demo1/AICharacter/AICharacter_LongRange.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UParticleSystem;
class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;
class UDamageType;

UCLASS()
class DEMO1_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 重叠事件
	UFUNCTION()
	void OnOverlayBegin(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 初始化一下发射物
	UFUNCTION()
	void Init(AAICharacter_Base* OwnerCharacter);

	// 撞击之后的回调函数
	//UFUNCTION()
	//void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// 播放特效
	void PlayEffect();

	// 判断是否超出飞行范围
	UFUNCTION()
	bool IsOutOfFlightRange();

public:
	// 此投射物的基本组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ExplosionEffect;

	// 此投射物将造成的伤害类型和伤害。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

private:	
	// 飞行速度
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float M_FlightSpeed;

	// 飞行距离
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float M_FlightDistance;

	// 碰撞体积
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float M_CollisionRadius;

	// 爆炸特效
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	FSoftObjectPath M_ExplosionPath;

	// 模型
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	FSoftObjectPath M_MoudelPath;

	// 谁发射的
	UPROPERTY()
	AAICharacter_Base* M_OwnerCharacter;

	// 该发射物是哪个阵营的
	UPROPERTY()
	ECampType M_OwnerCampType;

	// 造成的伤害
	UPROPERTY()
	float M_Damage;

	// 创建的位置，用于判断飞行距离
	UPROPERTY()
	FVector M_CreateLocation;
};
