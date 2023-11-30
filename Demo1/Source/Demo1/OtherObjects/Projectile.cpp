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

	// 定义将作为投射物及其碰撞的根组件的SphereComponent。
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereComponent->InitSphereRadius(12.5f);
	SphereComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = SphereComponent;

	// 定义将作为视觉呈现的网格体。
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	if (DefaultMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(DefaultMesh.Object);
		StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -12.5f));
		StaticMesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	}

	// 定义投射物移动组件。
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

	// 检查是否超出飞行距离
	if (IsOutOfFlightRange())
	{
		Destroy();
	}
}

void AProjectile::OnOverlayBegin(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 对面死亡，或者同一阵营则跳过
	AAICharacter_Base* HitAI = Cast<AAICharacter_Base>(Other);
	AProjectile* HitProjectile = Cast<AProjectile>(Other);

	// 撞到 AI
	if (HitAI)
	{
		// 如果 AI 死了或者同阵营则穿过，否则爆炸
		if (!(HitAI->IsDead() || HitAI->GetCampType() == M_OwnerCampType))
		{
			UGameplayStatics::ApplyDamage(HitAI, M_Damage, GetInstigator()->GetController(), this, TSubclassOf<UDamageType>(UDamageType::StaticClass()));
			PlayEffect();
			Destroy();
		}
	}
	// 排除同类，撞到其他的东西，直接爆炸
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

	// 初始化一下数据
	M_OwnerCharacter = OwnerCharacter;
	if (M_OwnerCharacter)
	{
		M_OwnerCampType = M_OwnerCharacter->GetCampType();
		M_Damage = M_OwnerCharacter->GetAtk();
		M_CreateLocation = GetActorLocation();
	}

	// 注册一下重叠事件
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

