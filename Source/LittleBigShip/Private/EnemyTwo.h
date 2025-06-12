// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyTwo.generated.h"
class UBoxComponent;
UCLASS()
class AEnemyTwo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyTwo();
	void Actoroffset(float Deltatime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UStaticMeshComponent* Spaceship;

	
};
