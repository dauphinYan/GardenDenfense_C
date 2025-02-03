#include "MoveToBTTask.h"
#include "GardenDefence_C/Enemy/Zombie/ZombieController.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMoveToBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));

	if (Target)
	{
		FVector TargetLocation = Target->GetActorLocation();
		FRotator CurrentRotation = AIController->GetControlRotation();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(AIController->GetPawn()->GetActorLocation(), TargetLocation);

		//FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);
		//AIController->SetControlRotation(SmoothRotation);
		//AIController->GetPawn()->SetActorRotation(SmoothRotation);

		//if (UPathFollowingComponent* PathFollowingComp = AIController->GetPathFollowingComponent())
		//{
		//	// ͨ������ϵͳ��ʼ�ƶ�
		//	FNavLocation NavLocation;
		//	if (UNavigationSystemV1::GetNavigationSystem(GetWorld())->ProjectPointToNavigation(TargetLocation, NavLocation))
		//	{
		//		AIController->MoveToLocation(NavLocation);
		//	}
		//}

		//AIController->MoveToLocation(TargetLocation);

		// ���AI����Ŀ���㹻�ӽ������Է��سɹ�״̬
		if (FVector::Dist(AIController->GetPawn()->GetActorLocation(), TargetLocation) < 100.f)
		{
			return EBTNodeResult::Succeeded;
		}

		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}
