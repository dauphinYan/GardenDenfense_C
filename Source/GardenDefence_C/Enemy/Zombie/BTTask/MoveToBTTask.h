// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToBTTask.generated.h"

/**
 * 
 */
UCLASS()
class GARDENDEFENCE_C_API UMoveToBTTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere)
    float RotationSpeed = 5.0f;
};
