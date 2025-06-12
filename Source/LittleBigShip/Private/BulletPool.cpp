// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletPool.h"
#include "Bullet.h"



// Sets default values
ABulletPool::ABulletPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}


// Called when the game starts or when spawned
void ABulletPool::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ABulletPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABulletPool::InstanstiateOBJ(int32 PoolSize,TSubclassOf<AActor> InBullet,FVector Spawnlocation,FRotator SpawnRotator)
{
	Bullet = InBullet;
	Pool.Empty();
	for(int i=0;i<PoolSize;i++)
	{
		AActor* SpawnActor= GetWorld()->SpawnActor<AActor>(InBullet, Spawnlocation, SpawnRotator);
		SpawnActor->SetActorHiddenInGame(true);
		SpawnActor->SetActorEnableCollision(false);
		SpawnActor->SetActorTickEnabled(false);
		if(ABullet* BulletActor = Cast<ABullet>(SpawnActor))
		{
			/*FVector Direction =SpawnRotator.Vector();*/
		}
		Pool.Add(SpawnActor);
		UE_LOG(LogTemp,Warning,TEXT("This is instantiate working"))
	}
}

AActor* ABulletPool::GetBullet(FVector Spawnlocation,FRotator SpawnRotator)
{
	for(AActor* Object : Pool)
	{
		if(Object->IsHidden())
		{
			Object->SetActorLocation(Spawnlocation);
			Object->SetActorRotation(SpawnRotator);
			Object->SetActorHiddenInGame(false);
			Object->SetActorEnableCollision(true);
			Object->SetActorTickEnabled(false);
			if(ABullet* BulletActor = Cast<ABullet>(Object))
			{
				FVector Direction =SpawnRotator.Vector();// To get the forward vector use the rotation
			}
			UE_LOG(LogTemp,Warning,TEXT("This is Get working"))
			return Object;
		}
	}
	AActor* SpawnActor =GetWorld()->SpawnActor<AActor>(Bullet, Spawnlocation, SpawnRotator);
	Pool.Add(SpawnActor);
	return SpawnActor;
}
void ABulletPool::ReturnBullet(AActor* bull)
{
	bull->SetActorHiddenInGame(true);
	bull->SetActorEnableCollision(false);
	bull->SetActorTickEnabled(true);
}


