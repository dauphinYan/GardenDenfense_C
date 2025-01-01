// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"  
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Attack;

	UPROPERTY(EditAnywhere,Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere,Category="Camera")
	class UCameraComponent* Camera;
};
