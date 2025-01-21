#include "Actor_SnowPeaShooter.h"
#include "GardenDefence_C/Plant/BulletPool.h"
#include "GardenDefence_C/Plant/BulletBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"

AActor_SnowPeaShooter::AActor_SnowPeaShooter()
{
	BulletPool = CreateDefaultSubobject<UBulletPool>(TEXT("BulletPool"));
	EquippedPlantName = EEquippedPlantName::EPN_SnowPea;
}

void AActor_SnowPeaShooter::BeginPlay()
{
	Super::BeginPlay();

	if (BulletPool)
	{
		BulletPool->InitializePool();
	}
}

void AActor_SnowPeaShooter::AttackEnemy()
{
	if (TargetEnemy)
	{
		if (!ShootHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &AActor_SnowPeaShooter::FireBullet, 0.1f, true);

		}
	}
}

void AActor_SnowPeaShooter::FireBullet()
{
	if (ShotsRemaining > 0)
	{
		FVector Direction = TargetEnemy->GetActorLocation() - GetActorLocation();
		Direction.Z = 0;
		FRotator LookAtRotation = Direction.Rotation();
		SetActorRotation(LookAtRotation);

		ABulletBase* Bullet = BulletPool->GetBullet();
		if (Bullet)
		{
			Bullet->ActivateBullet(GetActorLocation(), LookAtRotation.Vector(), Damage);
		}
		ShotsRemaining--;

		if (ShotsRemaining <= 0)
		{
			ShotsRemaining = NumShots;
			GetWorld()->GetTimerManager().ClearTimer(ShootHandle);
		}
	}
}
