#define ECC_PlantArea ECollisionChannel::ECC_GameTraceChannel1

#include "MainPlayerController.h"
#include "GardenDefence_C/Widget/UserWidget_MainUI.h"
#include "GardenDefence_C/Widget/GamePlayHUD.h"
#include "TimerManager.h"
#include "GardenDefence_C/Plant/Actor_PrePlacedPlant.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GardenDefence_C/Interface/Interface_PlantedArea.h"

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
		FRotator Rotation = FRotator::ZeroRotator;
		PrePlant = GetWorld()->SpawnActor<AActor_PrePlacedPlant>(PrePlantClass, Location, Rotation);
	}
	CharacterHUD = Cast<AGamePlayHUD>(GetHUD());
	GrowSoundWave = LoadObject<USoundWave>(nullptr, TEXT("SoundWave'/Game/Audio/SoundEffect/Plant/growplant.growplant'"));

	// Uploading grow placedplant logic.
	GetWorld()->GetTimerManager().SetTimer(PrePlantHandle, this, &AMainPlayerController::SetPrePlantLocation, 0.01f, true);
	GetWorld()->GetTimerManager().PauseTimer(PrePlantHandle);

}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IA_Cancel, ETriggerEvent::Started, this, &AMainPlayerController::OnCanceledButtonPressed);
	}
}

void AMainPlayerController::OnCanceledButtonPressed()
{
	OnCanceledSelectPlant();
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
	PlacedPlantName = InPlacedPlantName;
	if (PrePlant == nullptr) return;
	PrePlant->SetPlacedPlant(PlacedPlantName);
}

void AMainPlayerController::OnCanceledSelectPlant()
{
	OperationState = EOperationState::EOS_Unoccupied;
	//GetWorld()->GetTimerManager().PauseTimer(PrePlantHandle);
	PlacedPlantName = EPlacedPlantName::PPN_DefaultMax;
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
	if (PlacedPlantArea)
	{
		if (IInterface_PlantedArea* InPlantedArea = Cast<IInterface_PlantedArea>(PlacedPlantArea))
		{
			InPlantedArea->GrowPlant(PlacedPlantName);
		}
	}
	OnCanceledSelectPlant();
}

FVector AMainPlayerController::GetCursorLocation()
{
	FHitResult HitResult;
	if (GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult))
	{
		return HitResult.Location;
	}
	return FVector::ZeroVector;
}



void AMainPlayerController::SetPrePlantLocation()
{
	if (PrePlant == nullptr) return;
	if (OperationState != EOperationState::EOS_SelectingPlant)
		return;
	FHitResult HitResult;
	if (GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult))
	{
		FVector Location = HitResult.Location;
		if (PrePlant)
		{
			PrePlant->SetActorLocation(Location);
		}
		FVector DetectLocation = Location;
		DetectLocation.Z = 100.f;
		FHitResult PlantAreaHitResult;
		FVector Start = DetectLocation;
		DetectLocation.Z = -500.f;
		FVector End = DetectLocation;

		// 执行线性追踪
		bool bHit = GetWorld()->LineTraceSingleByChannel(PlantAreaHitResult, Start, End, ECC_PlantArea);

		// 绘制射线，颜色根据是否命中改变
		FColor LineColor = bHit ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), Start, End, LineColor, false, 5.0f, 0, 2.0f);

		if (bHit)
		{

			PlacedPlantArea = PlantAreaHitResult.GetActor();
			if (PlacedPlantArea)
			{
			}
		}
		else
		{
			PlacedPlantArea = nullptr;
		}
	}
}

