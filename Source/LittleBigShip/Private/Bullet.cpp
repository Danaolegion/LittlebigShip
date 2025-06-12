// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "BulletPool.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Boxcollision=CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent=Boxcollision;
	
	Bullet=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent=Bullet;
	
	BulletPool=Cast<ABulletPool>(UGameplayStatics::GetActorOfClass(GetWorld(),ABulletPool::StaticClass()));

	ProjectileMovementComponent= CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	
}



void ABullet::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
                        FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if(Other &&(Other != this)&& OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet overlapped with: %s"), *Other->GetName());
		BulletPool->ReturnBullet(this);
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

