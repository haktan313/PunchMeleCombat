
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StatSystem/Interface_StatSystem.h"
#include "EnemyBase.generated.h"

UCLASS()
class PUNCHSYSTEM_API AEnemyBase : public ACharacter, public IInterface_StatSystem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TArray<class UAnimMontage*> meleeDamageMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TArray <class UAnimMontage*> meleeDeathMontage;

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

	class UAnimInstance* AnimInstance;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	virtual void TakeDamage_Implementation(FS_DamageInfo aboutDamage) override;

	UFUNCTION()
	void DamageResponse(E_DamageType damageType, int AttackWay);

	UFUNCTION()
	void DeathResponse(E_DeathType deathType, int AttackWay);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	class UStatSystemComponent* StatSystemComponent;

	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	class USoundCue* damageSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	TSubclassOf<class UCameraShakeBase> damageCameraShake;

};
