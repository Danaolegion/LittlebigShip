// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Chaser.generated.h"
class UBoxComponent;
class ASpaceship;

UCLASS()
class AEnemyOne : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyOne();
	void Actoroffset(float Deltatime);
	UPROPERTY(EditAnywhere, Category="Follow")
	float followspeed = 1.f;
	float TimeLimit;
	FTimerHandle TimerHandle;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Spaceship;

	UPROPERTY(EditAnywhere, Category= "Follow")
	ASpaceship* Target;

	UFUNCTION()
	void Chase(float DeltaTime);

	UFUNCTION()
	void DestroyOverTimeLimit();

	UFUNCTION()
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation,
		FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
