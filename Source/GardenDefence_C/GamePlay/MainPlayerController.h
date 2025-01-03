#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;
	class AGamePlayHUD* CharacterHUD;

	UFUNCTION(BlueprintCallable)
	void SelectPlantInSeedBank(int32 Index);

private:
};
