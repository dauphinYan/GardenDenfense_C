#include "Pea.h"

APea::APea()
{

}

void APea::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if (NiagaraSystem && GetWorld())
	//{
	//	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
	//		GetWorld(),
	//		NiagaraSystem,
	//		Hit.Location,
	//		FRotator::ZeroRotator,
	//		FVector(1.0f)
	//	);
	//	DrawDebugSphere(
	//		GetWorld(),
	//		Hit.Location,
	//		20.0f,                // �뾶
	//		12,                   // �ֶ���
	//		FColor::Green,        // ������ɫ
	//		false,                // �Ƿ�־���ʾ
	//		5.0f                  // ����ʱ��
	//	);
	//}

	//Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

void APea::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Pea overlapped with: %s"), *OtherActor->GetName());
	if (NiagaraSystem && GetWorld())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			NiagaraSystem,
			OtherActor->GetActorLocation(),
			FRotator::ZeroRotator,
			FVector(1.0f)
		);
	}

	DeactivateBullet();
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
//		20.0f,                // �뾶
//		12,                   // �ֶ���
//		FColor::Green,        // ������ɫ
//		false,                // �Ƿ�־���ʾ
//		5.0f                  // ����ʱ��
//	);
//}