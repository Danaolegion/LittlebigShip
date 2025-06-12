// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletPool.generated.h"
class ABullet;
class ASpaceship;
UCLASS()
 class  ABulletPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletPool();
	//ObjectPooling
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Spawning")
	TArray<AActor*> Pool;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Spawning")
	TSubclassOf<ABullet> Bullet;

	void InstanstiateOBJ(int32 PoolSize,TSubclassOf<AActor> InBullet,FVector Spawnlocation,FRotator SpawnRotator);//Create Bullet Pull
	AActor* GetBullet(FVector Spawnlocation,FRotator SpawnRotator);//take bullet from pool to the game
	void ReturnBullet(AActor* bull);//return the used bullet to the pool

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
