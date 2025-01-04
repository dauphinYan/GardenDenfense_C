#include "MainPlayerController.h"
#include "GardenDefence_C/Widget/UserWidget_MainUI.h"
#include "GardenDefence_C/Widget/GamePlayHUD.h"
#include "TimerManager.h"
#include "GardenDefence_C/Plant/Actor_PrePlacedPlant.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	CharacterHUD = Cast<AGamePlayHUD>(GetHUD());
	GetWorld()->GetTimerManager().SetTimer(PrePlantHandle, this, &AMainPlayerController::SetPrePlantLocation, 0.01f, true);
	OnSelectedPlant();
}

void AMainPlayerController::SelectPlantInSeedBank(int32 Index)
{
	CharacterHUD->SelectPlantInSeedBank(Index);
}

void AMainPlayerController::OnSelectedPlant()
{
	OperationState = EOperationState::EOS_SelectingPlant;
	GetWorld()->GetTimerManager().UnPauseTimer(PrePlantHandle);
}

void AMainPlayerController::OnCanceledSelectPlant()
{
	OperationState = EOperationState::EOS_Unoccupied;
	GetWorld()->GetTimerManager().PauseTimer(PrePlantHandle);
}

void AMainPlayerController::SetPrePlantLocation()
{
	if (PrePlant == nullptr && PrePlantClass != nullptr)
	{
		FVector Location = FVector::ZeroVector;
		FRotator Transform = FRotator::ZeroRotator;
		PrePlant = GetWorld()->SpawnActor<AActor_PrePlacedPlant>(PrePlantClass, Location, Transform);
	}
	if (OperationState != EOperationState::EOS_SelectingPlant)
		return;
	FVector WorldLocation;
	FVector WorldDirection;
	if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FHitResult HitResult;
		FVector Start = WorldLocation;
		FVector End = Start + (WorldDirection * 10000.f);
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.1f, 0, 0.1f);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
		{
			PrePlant->SetActorLocation(HitResult.Location);
			
		}
	}
}

