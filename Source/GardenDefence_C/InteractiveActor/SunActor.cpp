#include "SunActor.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GardenDefence_C/GamePlay/MainGameStateBase.h"
#include "GardenDefence_C/Widget/GamePlayHUD.h"

ASunActor::ASunActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	SunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SunMesh"));
	SunMesh->SetupAttachment(RootComponent);
	SunMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	SunMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	SunMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SunMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	SunMesh->SetSimulatePhysics(true);
	SunMesh->OnClicked.AddDynamic(this, &ASunActor::MeshOnClicked);
	SunMesh->OnComponentBeginOverlap.AddDynamic(this, &ASunActor::OnBeginOverlap);
}

void ASunActor::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
	GameState = Cast<AMainGameStateBase>(GetWorld()->GetGameState());
}

void ASunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASunActor::MeshOnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	SelectSun();
}

void ASunActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SelectSun();
}

void ASunActor::SelectSun()
{
	GameState = GameState == nullptr ? Cast<AMainGameStateBase>(GetWorld()->GetGameState()) : GameState;
	GameState->AddSunValue(SunValue);
	SetActorHiddenInGame(true);
	SunMesh->SetSimulatePhysics(false);
	SunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AGamePlayHUD* GamePlayHUD = Cast<AGamePlayHUD>(PlayerController->GetHUD());
	if (GamePlayHUD)
	{
		FVector2D ActorScreenPosition;
		if (PlayerController && UGameplayStatics::ProjectWorldToScreen(PlayerController, SunMesh->GetComponentLocation(), ActorScreenPosition))
		{
			GamePlayHUD->PlaySunSelectedAnimation(ActorScreenPosition);
		}
	}
	Destroy();
}
