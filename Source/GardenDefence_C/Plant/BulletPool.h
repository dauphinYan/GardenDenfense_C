#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GARDENDEFENCE_C_API UBulletPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBulletPool();

	void InitializePool(TSubclassOf<class ABullet> BulletClass, int32 PoolSize);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TArray<class ABullet*> BulletPool;

	UPROPERTY()
	TSubclassOf<ABullet> BulletClass;
};
