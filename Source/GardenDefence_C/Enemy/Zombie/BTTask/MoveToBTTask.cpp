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
		//	// 通过导航系统开始移动
		//	FNavLocation NavLocation;
		//	if (UNavigationSystemV1::GetNavigationSystem(GetWorld())->ProjectPointToNavigation(TargetLocation, NavLocation))
		//	{
		//		AIController->MoveToLocation(NavLocation);
		//	}
		//}

		//AIController->MoveToLocation(TargetLocation);

		// 如果AI距离目标足够接近，可以返回成功状态
		if (FVector::Dist(AIController->GetPawn()->GetActorLocation(), TargetLocation) < 100.f)
		{
			return EBTNodeResult::Succeeded;
		}

		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}
