#include "AttackBTTask.h"
#include "GardenDefence_C/Enemy/Zombie/ZombieController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UAttackBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		AZombieController* ZombieController = Cast<AZombieController>(AIController);
		if (ZombieController)
		{
			ZombieController->SetCharacterAttackingBool(true);
		}
		AActor* Target = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("Target"));
		if (Target)
		{
			FVector CurrentLocation = AIController->GetPawn()->GetActorLocation();
			FVector TargetLocation = Target->GetActorLocation();

			FRotator TargetRotation = (TargetLocation - CurrentLocation).Rotation();
			AIController->GetPawn()->SetActorRotation(TargetRotation);
		}
	}

	return EBTNodeResult::Succeeded;
}
