

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "StatSystem/Structure_StatSystem.h"
#include "PunchPlayerCharacter.generated.h"

UCLASS()
class PUNCHSYSTEM_API APunchPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Camera,meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* springArm;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Camera,meta=(AllowPrivateAccess="true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	class UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Animation,meta=(AllowPrivateAccess="true"))
	TArray<class UAnimMontage*> AttackMontages;
	class UAnimMontage* CurrentAttackMontage;

	class UAnimInstance* AnimInstance;

public:

	APunchPlayerCharacter();

	bool bDoOnce = true;

	bool bAttackCombo = false;

	int comboCount = 0;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Attack,meta=(AllowPrivateAccess="true"))
	TArray<FName> AttackSocketNames;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Attack,meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UCameraShakeBase> punchCameraShake;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Attack,meta=(AllowPrivateAccess="true"))
	class USoundCue* punchSound;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Attack();

	FS_DamageInfo damageInfo;

	void AttackComboContinue();

	void AttackComboEnd();

};
