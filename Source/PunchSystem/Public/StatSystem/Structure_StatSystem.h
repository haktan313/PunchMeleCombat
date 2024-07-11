#pragma once

#include "CoreMinimal.h"
#include "Enum_StatSystem.h"
#include "Structure_StatSystem.generated.h"

USTRUCT(BlueprintType)
struct FS_DamageInfo
{
	GENERATED_BODY()

	FS_DamageInfo()
		: AmountOfDamage(0.f), DamageType(E_DamageType::Melee), DeathType(E_DeathType::Melee), AttackWay(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AmountOfDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_DamageType DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_DeathType DeathType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AttackWay;
};