// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/AssetManager.h"
//#include "Demo1/AICharacter/AICharacter_Base.h"
//#include "IDamageInterface.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageType = UDamageType::StaticClass();

	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (DefaultExplosionEffect.Succeeded())
	{
		ExplosionEffect = DefaultExplosionEffect.Object;
	}

	// ���彫��ΪͶ���Ｐ����ײ�ĸ������SphereComponent��
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereComponent->InitSphereRadius(12.5f);
	SphereComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = SphereComponent;

	// ���彫��Ϊ�Ӿ����ֵ������塣
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	if (DefaultMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(DefaultMesh.Object);
		StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -12.5f));
		StaticMesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	}

	// ����Ͷ�����ƶ������
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(SphereComponent);
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
	ProjectileMovementComponent->MaxSpeed = 1500.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ����Ƿ񳬳����о���
	if (IsOutOfFlightRange())
	{
		Destroy();
	}
}

void AProjectile::OnOverlayBegin(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ��������������ͬһ��Ӫ������
	AAICharacter_Base* HitAI = Cast<AAICharacter_Base>(Other);
	AProjectile* HitProjectile = Cast<AProjectile>(Other);

	// ײ�� AI
	if (HitAI)
	{
		// ��� AI ���˻���ͬ��Ӫ�򴩹�������ը
		if (!(HitAI->IsDead() || HitAI->GetCampType() == M_OwnerCampType))
		{
			UGameplayStatics::ApplyDamage(HitAI, M_Damage, GetInstigator()->GetController(), this, TSubclassOf<UDamageType>(UDamageType::StaticClass()));
			PlayEffect();
			Destroy();
		}
	}
	// �ų�ͬ�࣬ײ�������Ķ�����ֱ�ӱ�ը
	else if(HitProjectile == nullptr)
	{
		PlayEffect();
		Destroy();
	}
}

void AProjectile::Init(AAICharacter_Base* OwnerCharacter)
{
	DamageType = UDamageType::StaticClass();

	UParticleSystem* NewExplosion = UAssetManager::GetStreamableManager().LoadSynchronous<UParticleSystem>(M_ExplosionPath.GetAssetPathString(), false, nullptr);
	if (NewExplosion)
	{
		ExplosionEffect = NewExplosion;
	}

	SphereComponent->InitSphereRadius(M_CollisionRadius);

	UStaticMesh* NewStaticMesh = UAssetManager::GetStreamableManager().LoadSynchronous<UStaticMesh>(M_MoudelPath.GetAssetPathString(), false, nullptr);
	if (NewStaticMesh)
	{
		StaticMesh->SetStaticMesh(NewStaticMesh);
	}

	ProjectileMovementComponent->InitialSpeed = M_FlightSpeed;
	ProjectileMovementComponent->MaxSpeed = M_FlightSpeed;

	// ��ʼ��һ������
	M_OwnerCharacter = OwnerCharacter;
	if (M_OwnerCharacter)
	{
		M_OwnerCampType = M_OwnerCharacter->GetCampType();
		M_Damage = M_OwnerCharacter->GetAtk();
		M_CreateLocation = GetActorLocation();
	}

	// ע��һ���ص��¼�
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlayBegin);
}

void AProjectile::PlayEffect()
{
	FVector spawnLocation = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, spawnLocation, FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
}

bool AProjectile::IsOutOfFlightRange()
{
	float Dis = FVector::Distance(GetActorLocation(), M_CreateLocation);
	return Dis >= M_FlightDistance;
}

