#include "Pea.h"

APea::APea()
{

}

void APea::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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


//if (NiagaraSystem && GetWorld())
//{
//	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
//		GetWorld(),
//		NiagaraSystem,
//		OtherActor->GetActorLocation(),
//		FRotator::ZeroRotator,
//		FVector(1.0f)
//	);
//	DrawDebugSphere(
//		GetWorld(),
//		OtherActor->GetActorLocation(),
//		20.0f,                // 半径
//		12,                   // 分段数
//		FColor::Green,        // 球体颜色
//		false,                // 是否持久显示
//		5.0f                  // 持续时间
//	);
//}