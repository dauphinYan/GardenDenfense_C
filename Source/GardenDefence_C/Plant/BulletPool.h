#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletPool.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GARDENDEFENCE_C_API UBulletPool : public UActorComponent
{
	GENERATED_BODY()

public:
	UBulletPool();

	void InitializePool();
	class ABulletBase* GetBullet();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TArray<ABulletBase*> BulletPool;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	TSubclassOf<ABulletBase> BulletClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	int32 PoolSize = 1;
};
