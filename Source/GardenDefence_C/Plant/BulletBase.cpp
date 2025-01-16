#define ECC_Enemy ECollisionChannel::ECC_GameTraceChannel2

#include "BulletBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GardenDefence_C/Plant/BulletPool.h"

ABulletBase::ABulletBase()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionBox"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Enemy, ECollisionResponse::ECR_Overlap);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABulletBase::OnHit);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABulletBase::OnBeginOverlap);

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

void ABulletBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void ABulletBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
