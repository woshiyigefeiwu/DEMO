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

	// �ص��¼�
	UFUNCTION()
	void OnOverlayBegin(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// ��ʼ��һ�·�����
	UFUNCTION()
	void Init(AAICharacter_Base* OwnerCharacter);

	// ײ��֮��Ļص�����
	//UFUNCTION()
	//void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// ������Ч
	void PlayEffect();

	// �ж��Ƿ񳬳����з�Χ
	UFUNCTION()
	bool IsOutOfFlightRange();

public:
	// ��Ͷ����Ļ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ExplosionEffect;

	// ��Ͷ���ｫ��ɵ��˺����ͺ��˺���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

private:	
	// �����ٶ�
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float M_FlightSpeed;

	// ���о���
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float M_FlightDistance;

	// ��ײ���
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	float M_CollisionRadius;

	// ��ը��Ч
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	FSoftObjectPath M_ExplosionPath;

	// ģ��
	UPROPERTY(EditAnywhere, Category = "BaseConfig")
	FSoftObjectPath M_MoudelPath;

	// ˭�����
	UPROPERTY()
	AAICharacter_Base* M_OwnerCharacter;

	// �÷��������ĸ���Ӫ��
	UPROPERTY()
	ECampType M_OwnerCampType;

	// ��ɵ��˺�
	UPROPERTY()
	float M_Damage;

	// ������λ�ã������жϷ��о���
	UPROPERTY()
	FVector M_CreateLocation;
};
