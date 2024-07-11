

#pragma once

#include "CoreMinimal.h"
#include "Structure_StatSystem.h"
#include "Components/ActorComponent.h"
#include "StatSystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeath, E_DeathType, DeathType,int,AttackWay);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageResponse, E_DamageType, DamageType,int,AttackWay);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUNCHSYSTEM_API UStatSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	void TakeDamage(FS_DamageInfo aboutDamage);

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable)
	FOnDamageResponse OnDamageResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float currentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float maxHealth;

	bool bIsDead = false;
};
