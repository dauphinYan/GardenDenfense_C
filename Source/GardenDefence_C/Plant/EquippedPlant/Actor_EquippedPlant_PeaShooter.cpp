#include "Actor_EquippedPlant_PeaShooter.h"
#include "GardenDefence_C/Plant/BulletPool.h"
#include "GardenDefence_C/Plant/BulletBase.h"

AActor_EquippedPlant_PeaShooter::AActor_EquippedPlant_PeaShooter()
{
	BulletPool = CreateDefaultSubobject<UBulletPool>(TEXT("BulletPool"));
}

void AActor_EquippedPlant_PeaShooter::BeginPlay()
{
	Super::BeginPlay();

	if (BulletPool)
	{
		BulletPool->InitializePool();
	}
}

void AActor_EquippedPlant_PeaShooter::AttackEnemy()
{
	if (TargetEnemy)
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
	}
}

