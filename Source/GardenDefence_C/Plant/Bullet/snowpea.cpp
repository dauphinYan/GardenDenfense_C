// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowPea.h"

ASnowPea::ASnowPea()
{
}

void ASnowPea::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HitNiagaraSystem && GetWorld())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			HitNiagaraSystem,
			OtherActor->GetActorLocation(),
			FRotator::ZeroRotator,
			FVector(1.0f)
		);
	}

	if (OtherActor)
	{
		if (IInterface_Enemy* InOtherActor = Cast<IInterface_Enemy>(OtherActor))
		{
			if (InOtherActor->IsAlive())
			{
				UGameplayStatics::ApplyDamage(
					OtherActor,
					BulletDamage,
					GetInstigatorController(),
					this,
					UDamageType::StaticClass()
				);
			}
		}

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, OtherActor->GetActorLocation());
		}

		DeactivateBullet();
	}
}
