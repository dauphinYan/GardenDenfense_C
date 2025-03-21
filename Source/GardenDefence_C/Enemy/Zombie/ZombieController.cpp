#include "ZombieController.h"
#include "GardenDefence_C/Character/MainCharacter.h"
#include "GardenDefence_C/Plant/Actor_PlacedPlant.h"
#include "GardenDefence_C/InteractiveActor/HomeActor.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

void AZombieController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree && BlackboardData)
	{
		UBlackboardComponent* BlackboardComponent = Blackboard;

		UseBlackboard(BlackboardData, BlackboardComponent);
		RunBehaviorTree(BehaviorTree);
	}

	GetWorld()->GetTimerManager().SetTimer(SearchHandle, this, &AZombieController::SearchTarget, 1.f, true);
}

void AZombieController::SetCharacterAttackingBool(bool InBool)
{
	bIsAttacking = InBool;
	Blackboard->SetValueAsBool("bIsAttacking", InBool);
}

void AZombieController::SearchTarget()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
	{
		return;
	}

	// If the current target is a placed plant and is still valid, skip further searching.
	auto* TargetFromBlackboard = Blackboard->GetValueAsObject("Target");
	if (IsValid(TargetFromBlackboard))
	{
		if (TargetFromBlackboard->IsA(AActor_PlacedPlant::StaticClass()))
		{
			return;
		}
	}
	else
	{
		BestTarget = nullptr;
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
			// Priority 1: Check if it is the placed plant.
			if (OverlapActor->IsA(AActor_PlacedPlant::StaticClass()) || OverlapActor->IsA(AMainCharacter::StaticClass()))
			{
				float CurDistance = FVector::Dist(ZombieLocation, OverlapActor->GetActorLocation());
				if (CurDistance < ClosestDistance)
				{
					ClosestDistance = CurDistance;
					BestTarget = OverlapActor;
				}
			}
		}
		Blackboard->SetValueAsObject("Target", BestTarget);
	}
	else
	{
		BestTarget = nullptr;
		AActor* HomeTarget = UGameplayStatics::GetActorOfClass(GetWorld(), AHomeActor::StaticClass());
		if (HomeTarget != nullptr)
		{
			Blackboard->SetValueAsObject("Target", HomeTarget);
		}
	}

	if (BestTarget)
		DrawDebugSphere(GetWorld(), BestTarget->GetActorLocation(), 50.f, 24, FColor::Yellow, false, 1.0f);
}
