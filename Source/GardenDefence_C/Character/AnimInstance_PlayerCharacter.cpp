// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_PlayerCharacter.h"
#include "GardenDefence_C/Character/MainCharacter.h"

void UAnimInstance_PlayerCharacter::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
}

void UAnimInstance_PlayerCharacter::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	MainCharacter = MainCharacter == nullptr ? Cast<AMainCharacter>(TryGetPawnOwner()) : MainCharacter;
	if (MainCharacter == nullptr) return;

	FVector Velocity = MainCharacter->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();
}
