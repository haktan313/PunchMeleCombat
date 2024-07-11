#pragma once

#include "CoreMinimal.h"
#include "Enum_StatSystem.generated.h"

UENUM(BlueprintType)
enum class E_DamageType : uint8
{
	Melee UMETA(DisplayName = "Melee"),
};
UENUM(BlueprintType)
enum class E_DeathType : uint8
{
	Melee UMETA(DisplayName = "Melee"),
};