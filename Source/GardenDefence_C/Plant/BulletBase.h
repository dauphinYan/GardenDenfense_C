#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.generated.h"

UCLASS()
class GARDENDEFENCE_C_API ABulletBase : public AActor
{
	GENERATED_BODY()

public:
	ABulletBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void ActivateBullet(const FVector& Location, const FVector& Direction);
	void DeactivateBullet();

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BulletMesh;
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* ProjectileMovement;

	bool bInUse = false;

	FTimerHandle DeactivateTimerHandle;
public:
	FORCEINLINE bool IsInUse() { return bInUse; };
};
