#include "Actor_EquippedPlant_PeaShooter.h"

void AActor_EquippedPlant_PeaShooter::SearchEnemy()
{
	FVector Location = GetActorLocation();
	TArray<FOverlapResult> OverlapResults;

	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(AtkRange);
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	bool bHasHit = GetWorld()->OverlapMultiByChannel(OverlapResults, Location, FQuat::Identity, ECC_Enemy, CollisionShape, CollisionQueryParams);

	if (bHasHit)
	{
		float ClosestDistance = FLT_MAX;
		AActor* ClosestEnemy = nullptr;
		for (FOverlapResult Result : OverlapResults)
		{
			AActor* Enemy = Result.GetActor();
			float Distance = (Enemy->GetActorLocation() - Location).Size();
			if (ClosestDistance > Distance)
			{
				ClosestDistance = Distance;
				ClosestEnemy = Enemy;
			}
		}
		TargetEnemy = ClosestEnemy;
	}
	else
		TargetEnemy = nullptr;
}

void AActor_EquippedPlant_PeaShooter::AttackEnemy()
{
	if (TargetEnemy)
	{
		FVector Direction = TargetEnemy->GetActorLocation() - GetActorLocation();
		Direction.Z = 0;

		FRotator LookAtRotation = Direction.Rotation();

		SetActorRotation(LookAtRotation);
	}
}

