// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Spaceship.generated.h"


class UFloatingPawnMovement;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class ABullet;
class ABulletPool;


UCLASS()
class ASpaceship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceship();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawing")
	TSubclassOf<class AActor> Bullet;

	UPROPERTY(EditAnywhere,Category="Pooling")
	ABulletPool* BulletPool;

	FVector CurrentVelocity;

		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Components
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Spaceship;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* Spawnlocation;

	//Inputs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* ScaleSwitchAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* BulletFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFloatingPawnMovement* FloatingPawnMovement;
	//Function
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire();
	void SwitchScale();
	
	
	
};
