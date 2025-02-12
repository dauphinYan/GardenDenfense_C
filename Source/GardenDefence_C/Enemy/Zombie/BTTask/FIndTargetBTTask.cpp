#define ECC_Enemy ECollisionChannel::ECC_GameTraceChannel2
#define ECC_PlacedPlant ECollisionChannel::ECC_GameTraceChannel3

#include "FIndTargetBTTask.h"
#include "AIController.h"
#include "GardenDefence_C/Plant/Actor_PlacedPlant.h"
#include "GardenDefence_C/Character/MainCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GardenDefence_C/InteractiveActor/HomeActor.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UFIndTargetBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	float LastSearchTime = 0.0f;
	const float SearchInterval = 1.f;

	if (GetWorld()->GetTimeSeconds() - LastSearchTime < SearchInterval)
	{
		return EBTNodeResult::Succeeded;
	}
	LastSearchTime = GetWorld()->GetTimeSeconds();

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject("Target"));

	if (Target && !Target->IsA(AHomeActor::StaticClass()))
	{
		return EBTNodeResult::Succeeded;
	}

	FVector ZombieLocation = ControlledPawn->GetActorLocation();
	TArray<FOverlapResult> OverlapResult;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PlacedPlant);
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(800.f);

	bool bHasOverlap = GetWorld()->OverlapMultiByObjectType(
		OverlapResult,
		ZombieLocation,
		FQuat::Identity,
		ObjectQueryParams,
		CollisionShape
	);

	float ClosestDistance = 1000.f;

	if (bHasOverlap)
	{
		for (const FOverlapResult& Result : OverlapResult)
		{
			AActor* OverlapActor = Result.GetActor();
			// Priority 1: Check if the actor is the player character.
			if (OverlapActor->IsA(AMainCharacter::StaticClass()))
			{
				Target = OverlapActor;
				break;
			}
			// Priority 2: Check if it is the placed plant.
			if (OverlapActor->IsA(AActor_PlacedPlant::StaticClass()))
			{
				float CurDistance = FVector::Dist(ZombieLocation, OverlapActor->GetActorLocation());
				if (!Target || CurDistance < ClosestDistance)
				{
					ClosestDistance = CurDistance;
					Target = OverlapActor;
				}
			}
		}
		if (Target)
		{
			Blackboard->SetValueAsObject("Target", Target);
			return EBTNodeResult::Succeeded;
		}
	}
	else
	{
		Target = nullptr;

	}
	return EBTNodeResult::Succeeded;
}
