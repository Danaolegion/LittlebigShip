// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTwo.h"
#include "LittleBigShip/DebugMacro.h"
#include "Components/BoxComponent.h"

// Sets default values
AEnemyTwo::AEnemyTwo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent= BoxComponent;

	Spaceship=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Spaceship->SetupAttachment(GetRootComponent());
}

void AEnemyTwo::Actoroffset(float Deltatime)
{
	float MovementRate= 50.f;
	AddActorWorldOffset(FVector(0,MovementRate*Deltatime,0));
	Draw_Vector_SingleFrame(GetActorLocation(),GetActorLocation()+GetActorRightVector())
}

// Called when the game starts or when spawned
void AEnemyTwo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyTwo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Actoroffset(DeltaTime);
}



