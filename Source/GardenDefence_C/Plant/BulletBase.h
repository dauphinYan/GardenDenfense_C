#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GardenDefence_C/Interface/Interface_Enemy.h"
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

	void ActivateBullet(const FVector& Location, const FVector& Direction, float InBulletDamage);
	void DeactivateBullet();

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* CollisionComponent;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* TailNiagaraComponent;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* HitNiagaraSystem;

	UPROPERTY(EditDefaultsOnly)
	USoundWave* HitSound;

	UPROPERTY(EditDefaultsOnly)
	USoundWave* EmitterSound;

	float BulletDamage = 1;;

private:
	bool bInUse = false;

	FTimerHandle DeactivateTimerHandle;


public:
	FORCEINLINE bool IsInUse() { return bInUse; };
};
