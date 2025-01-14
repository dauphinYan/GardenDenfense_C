#include "BulletBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GardenDefence_C/Plant/BulletPool.h"

ABulletBase::ABulletBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	RootComponent = BulletMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void ABulletBase::BeginPlay()
{
	Super::BeginPlay();

}

void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABulletBase::ActivateBullet(const FVector& Location, const FVector& Direction)
{
	bInUse = true;
	SetActorLocation(Location);
	ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
	SetActorTickEnabled(true);
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);

	GetWorld()->GetTimerManager().SetTimer(DeactivateTimerHandle, this, &ABulletBase::DeactivateBullet, 5.0f, false);
}

void ABulletBase::DeactivateBullet()
{
	bInUse = false;
	ProjectileMovement->StopMovementImmediately();
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);

	GetWorld()->GetTimerManager().ClearTimer(DeactivateTimerHandle);
}

