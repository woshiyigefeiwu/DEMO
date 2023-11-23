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
//#include "IDamageInterface.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageType = UDamageType::StaticClass();

	//static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(*(M_ExplosionPath.ToString()));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (DefaultExplosionEffect.Succeeded())
	{
		ExplosionEffect = DefaultExplosionEffect.Object;
	}

	//���彫��ΪͶ���Ｐ����ײ�ĸ������SphereComponent��
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	//SphereComponent->InitSphereRadius(M_CollisionRadius);
	SphereComponent->InitSphereRadius(12.5f);
	SphereComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = SphereComponent;

	//���彫��Ϊ�Ӿ����ֵ������塣
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(*(M_MoudelPath.ToString()));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	if (DefaultMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(DefaultMesh.Object);
		StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -12.5f));
		StaticMesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	}

	//����Ͷ�����ƶ������
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(SphereComponent);
	//ProjectileMovementComponent->InitialSpeed = M_FlightSpeed;
	//ProjectileMovementComponent->MaxSpeed = M_FlightSpeed;
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
	ProjectileMovementComponent->MaxSpeed = 1500.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	//�ڻ����¼���ע���Ͷ����ײ��������
	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileImpact);

	UE_LOG(LogTemp, Error, TEXT("this is AProjectile::AProjectile(), %f"), M_FlightSpeed);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Error, TEXT("this is AProjectile::BeginPlay(), %f"), M_FlightSpeed);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ����Ƿ񳬳����о���
	if (IsOutOfFlightRange())
	{
		Destroyed();
	}
}

void AProjectile::Init(AAICharacter_Base* OwnerCharacter)
{
	DamageType = UDamageType::StaticClass();

	// ��ʼ��һ������
	//FString ExplosionPath = M_ExplosionPath.ToString();
	//const TCHAR* ObjectToFind_1 = *ExplosionPath;
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	//if (DefaultExplosionEffect.Succeeded())
	//{
	//	ExplosionEffect = DefaultExplosionEffect.Object;
	//}

	UParticleSystem* NewExplosion = UAssetManager::GetStreamableManager().LoadSynchronous<UParticleSystem>(M_ExplosionPath.GetAssetPathString(), false, nullptr);
	if (NewExplosion)
	{
		//StaticMesh->SetStaticMesh(NewExplosion);
		ExplosionEffect = NewExplosion;
	}

	SphereComponent->InitSphereRadius(M_CollisionRadius);

	//FString MoudelPath = M_MoudelPath.ToString();
	//const TCHAR* ObjectToFind_2 = *MoudelPath;
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	//if (DefaultMesh.Succeeded())
	//{
	//	StaticMesh->SetStaticMesh(DefaultMesh.Object);
	//}

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
}

void AProjectile::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// ��������������ͬһ��Ӫ������
	AAICharacter_Base* HitAI = Cast<AAICharacter_Base>(OtherActor);
	if (HitAI == nullptr || HitAI->IsDead() || HitAI->GetCampType() == M_OwnerCampType)
	{
		return;
	}

	UGameplayStatics::ApplyPointDamage(OtherActor, M_Damage, NormalImpulse, Hit, GetInstigator()->Controller, this, DamageType);

	Destroy();
}

void AProjectile::Destroyed()
{
	FVector spawnLocation = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, spawnLocation, FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
}

bool AProjectile::IsOutOfFlightRange()
{
	float Dis = FVector::Distance(GetActorLocation(), M_CreateLocation);
	return Dis >= M_FlightDistance;
}

