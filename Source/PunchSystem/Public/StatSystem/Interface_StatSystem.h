

#pragma once

#include "CoreMinimal.h"
#include "Structure_StatSystem.h"
#include "UObject/Interface.h"
#include "Interface_StatSystem.generated.h"

UINTERFACE(MinimalAPI)
class UInterface_StatSystem : public UInterface
{
	GENERATED_BODY()
};

class PUNCHSYSTEM_API IInterface_StatSystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	void TakeDamage(FS_DamageInfo aboutDamage);
};
