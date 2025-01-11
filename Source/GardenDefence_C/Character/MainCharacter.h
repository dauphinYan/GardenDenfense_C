// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"  
#include "GardenDefence_C/Enum/OperationState.h"
#include "MainCharacter.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	//EnhancedInput
	void Move(const FInputActionValue& InputValue);
	void Attack(const FInputActionValue& InputValue);

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



private:

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Attack;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY()
	class AMainPlayerController* PlayerController;

	EOperationState OperationState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* CombatComponent;

public:
	FORCEINLINE UCombatComponent* GetCombatComponent()
	{
		if (CombatComponent) return CombatComponent;
		return nullptr;
	}
};
