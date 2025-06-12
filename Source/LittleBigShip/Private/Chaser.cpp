// Fill out your copyright notice in the Description page of Project Settings.


#include "Chaser.h"
#include "LittleBigShip/DebugMacro.h"
#include "Components/BoxComponent.h"
#include "Spaceship.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AEnemyOne::AEnemyOne()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent= BoxComponent;

	Spaceship=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Spaceship->SetupAttachment(GetRootComponent());
	Target= Cast<ASpaceship>(UGameplayStatics::GetActorOfClass(GetWorld(),ASpaceship::StaticClass()));
	TimeLimit =10.f;


}

void AEnemyOne::Actoroffset(float Deltatime)
{
	float MovementRate= 50.f;
	AddActorWorldOffset(FVector(MovementRate*Deltatime,0,0));
	
	
}


// Called when the game starts or when spawned
void AEnemyOne::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AEnemyOne::DestroyOverTimeLimit,TimeLimit,false);
}

// Called every frame
void AEnemyOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Actoroffset(DeltaTime);
	Chase(DeltaTime);
}

// Called to bind functionality to input
void AEnemyOne::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void AEnemyOne::Chase(float DeltaTime)
{
	FVector3d CurrentPosition = GetActorLocation();
	FVector3d TargetPosition = Target->GetActorLocation();

	FVector NewPos = FMath::VInterpTo(CurrentPosition,TargetPosition,DeltaTime,followspeed);
	Draw_Vector_SingleFrame(GetActorLocation(),GetActorLocation()+GetActorForwardVector())
	SetActorLocation(NewPos);
}

void AEnemyOne::DestroyOverTimeLimit()
{
	UE_LOG(LogTemp, Warning, TEXT("Actor has reached its time limit and will be destroyed."));
	Destroy();
}

void AEnemyOne::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	//Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if(Other &&(Other != this) && OtherComp)
	{
		//UE_LOG(LogTemp,Warning,TEXT("Enemy collide with: %s"),*Other->GetName())
		Destroy();
	}
}

