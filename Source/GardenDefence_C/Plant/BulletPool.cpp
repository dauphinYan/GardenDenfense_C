#include "BulletPool.h"

UBulletPool::UBulletPool()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UBulletPool::InitializePool(TSubclassOf<class ABullet> BulletClass, int32 PoolSize)
{
	for (int32 i = 0; i < PoolSize; i++)
	{
        ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass);
		
	}
}



void UBulletPool::BeginPlay()
{
	Super::BeginPlay();

	
}

void UBulletPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

