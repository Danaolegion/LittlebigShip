// Fill out your copyright notice in the Description page of Project Settings.
#include "Spaceship.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "BulletPool.h"



// Sets default values
ASpaceship::ASpaceship()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider=CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent=BoxCollider;

	Spaceship=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Spaceship->SetupAttachment(BoxCollider);
	
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(BoxCollider);
	SpringArmComponent->TargetArmLength=1000;

	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	Spawnlocation=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	Spawnlocation->SetupAttachment(GetRootComponent());

	bUseControllerRotationYaw= true;
	bUseControllerRotationPitch=true;

	FloatingPawnMovement=CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("floating"));
	
	FloatingPawnMovement->MaxSpeed=1000;
}


// Called when the game starts or when spawned
void ASpaceship::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PlayerController= Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext,0);
		}
	}
	BulletPool->InstanstiateOBJ(5,Bullet,Spawnlocation->GetComponentLocation(),Spawnlocation->GetComponentRotation());
}

// Called every frame
void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ASpaceship::Move);
		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ASpaceship::Look);
		EnhancedInputComponent->BindAction(ScaleSwitchAction,ETriggerEvent::Started,this,&ASpaceship::SwitchScale);
		EnhancedInputComponent->BindAction(BulletFire,ETriggerEvent::Completed,this,&ASpaceship::Fire);
	}
}

void ASpaceship::Move(const FInputActionValue& Value)
{
	const float DirectionValue= Value.Get<float>();
	if(Controller && DirectionValue!=0.f)
	{
		FVector forward=GetActorForwardVector();
		AddMovementInput(forward,DirectionValue);
	}
}

void ASpaceship::Look(const FInputActionValue& Value)
{
	const FVector2d LookXY=Value.Get<FVector2d>();
	if(GetController())
	{
			AddControllerPitchInput(LookXY.Y);
			AddControllerYawInput(LookXY.X);
	}
		
}

void ASpaceship::SwitchScale()
{
	FVector CurrentScale=GetActorScale3D();
	if(CurrentScale.Equals(FVector(1,1,1)))
	{
		SetActorScale3D(FVector(5.f,5.f,5.f));
		SpringArmComponent->TargetArmLength=10000;
	}
	else
	{
		SetActorScale3D(FVector(1.f,1.f,1.f));
		SpringArmComponent->TargetArmLength=6000;
	}
}


void ASpaceship::Fire()
{
	if(BulletPool)
	{
		FVector Spawnloc=Spawnlocation->GetComponentLocation();
		FRotator SpawnRot= Spawnlocation->GetComponentRotation();
		BulletPool->GetBullet(Spawnloc,SpawnRot);
	}

}
