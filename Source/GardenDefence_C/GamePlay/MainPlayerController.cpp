#include "MainPlayerController.h"
#include "GardenDefence_C/Widget/UserWidget_MainUI.h"
#include "GardenDefence_C/Widget/GamePlayHUD.h"
#include "TimerManager.h"
#include "GardenDefence_C/Plant/Actor_PrePlacedPlant.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	if (PrePlant == nullptr && PrePlantClass != nullptr)
	{
		FVector Location = FVector::ZeroVector;
		FRotator Transform = FRotator::ZeroRotator;
		PrePlant = GetWorld()->SpawnActor<AActor_PrePlacedPlant>(PrePlantClass, Location, Transform);
	}
	CharacterHUD = Cast<AGamePlayHUD>(GetHUD());
	GetWorld()->GetTimerManager().SetTimer(PrePlantHandle, this, &AMainPlayerController::SetPrePlantLocation, 0.01f, true);
	GetWorld()->GetTimerManager().PauseTimer(PrePlantHandle);
	GrowSoundWave = LoadObject<USoundWave>(nullptr, TEXT("SoundWave'/Game/Audio/SoundEffect/Plant/growplant.growplant'"));
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	//if (EnhancedInputComponent)
	//{
	//	EnhancedInputComponent->BindAction(IA_Cancel, ETriggerEvent::Started, this, &AMainPlayerController::OnCanceledButtonPressed);
	//}
}

void AMainPlayerController::OnCanceledButtonPressed()
{

}

void AMainPlayerController::SelectPlantInSeedBank(int32 Index)
{
	if (CharacterHUD == nullptr) return;
	CharacterHUD->SelectPlantInSeedBank(Index);
}

void AMainPlayerController::OnSelectedPlant(EPlacedPlantName InPlacedPlantName)
{
	OperationState = EOperationState::EOS_SelectingPlant;
	GetWorld()->GetTimerManager().UnPauseTimer(PrePlantHandle);
	if (PrePlant == nullptr) return;
	PrePlant->SetPlacedPlant(InPlacedPlantName);
}

void AMainPlayerController::OnCanceledSelectPlant()
{
	OperationState = EOperationState::EOS_Unoccupied;
	GetWorld()->GetTimerManager().PauseTimer(PrePlantHandle);
	if (PrePlant == nullptr || CharacterHUD == nullptr) return;
	PrePlant->SetPlacedPlant(EPlacedPlantName::PPN_DefaultMax);
	CharacterHUD->CancelSelectPlantInSeedBank();
}

void AMainPlayerController::GrowPlacedPlant()
{
	if (GrowSoundWave)
	{
		UGameplayStatics::PlaySound2D(this, GrowSoundWave);
	}
	OnCanceledSelectPlant();
}



void AMainPlayerController::SetPrePlantLocation()
{
	if (PrePlant == nullptr) return;
	if (OperationState != EOperationState::EOS_SelectingPlant)
		return;
	FHitResult HitResult;
	if (GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult))
	{
		if (PrePlant)
		{
			PrePlant->SetActorLocation(HitResult.Location);
		}
	}

}

