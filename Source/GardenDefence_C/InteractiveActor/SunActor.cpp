#include "SunActor.h"

ASunActor::ASunActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	SunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SunMesh"));
	SunMesh->SetupAttachment(RootComponent);
}

void ASunActor::BeginPlay()
{
	Super::BeginPlay();

}

void ASunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

