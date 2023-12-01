// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionObject.h"
#include "Demo1/AICharacter/AICharacter_Base.h"

// Sets default values
AExplosionObject::AExplosionObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//RootComponent = StaticMesh;
	//if (DefaultMesh.Succeeded())
	//{
	//	StaticMesh->SetStaticMesh(DefaultMesh.Object);
	//	StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -12.5f));
	//	StaticMesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	//}
}

// Called when the game starts or when spawned
void AExplosionObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosionObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosionObject::Init(AAICharacter_Base* AI, FVector ExplosionRange, float ExplosionTime)
{
	//OwnerAI = AI;
	//AfterExplosionTime = ExplosionTime;
	//
	//StaticMesh->SetRelativeLocation(AI->GetActorLocation());
	//StaticMesh->SetRelativeScale3D(ExplosionRange);
}

