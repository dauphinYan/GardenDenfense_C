#include "BulletPool.h"
#include "BulletBase.h"

UBulletPool::UBulletPool()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UBulletPool::BeginPlay()
{
	Super::BeginPlay();


}

void UBulletPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UBulletPool::InitializePool()
{
	if (BulletClass)
	{
		for (int32 i = 0; i < PoolSize; i++)
		{
			ABulletBase* Bullet = GetWorld()->SpawnActor<ABulletBase>(BulletClass);
			BulletPool.Add(Bullet);
			Bullet->DeactivateBullet();
		}
	}

}

ABulletBase* UBulletPool::GetBullet()
{
	for (ABulletBase* Bullet : BulletPool)
	{
		if (!Bullet->IsInUse())
		{
			return Bullet;
		}
	}
	return nullptr;
}
