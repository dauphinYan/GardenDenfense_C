#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_Enemy.generated.h"

UINTERFACE(MinimalAPI)
class UInterface_Enemy : public UInterface
{
	GENERATED_BODY()
};

class GARDENDEFENCE_C_API IInterface_Enemy
{
	GENERATED_BODY()

public:
	virtual bool IsAlive();

};
