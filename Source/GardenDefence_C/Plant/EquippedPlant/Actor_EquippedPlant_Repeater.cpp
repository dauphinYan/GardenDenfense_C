#include "Actor_EquippedPlant_Repeater.h"
#include "GardenDefence_C/Plant/BulletPool.h"
#include "GardenDefence_C/Plant/BulletBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"

AActor_EquippedPlant_Repeater::AActor_EquippedPlant_Repeater()
{
	BulletPool = CreateDefaultSubobject<UBulletPool>(TEXT("BulletPool"));
}

void AActor_EquippedPlant_Repeater::BeginPlay()
{
	Super::BeginPlay();

	if (BulletPool)
	{
		BulletPool->InitializePool();
	}
}

void AActor_EquippedPlant_Repeater::AttackEnemy()
{
	if (TargetEnemy)
	{
		if (!ShootHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &AActor_EquippedPlant_Repeater::FireBullet, 0.1f, true);

		}
	}
}

void AActor_EquippedPlant_Repeater::FireBullet()
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

