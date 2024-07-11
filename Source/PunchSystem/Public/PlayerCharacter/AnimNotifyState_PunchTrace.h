

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_PunchTrace.generated.h"


UCLASS()
class PUNCHSYSTEM_API UAnimNotifyState_PunchTrace : public UAnimNotifyState
{
	GENERATED_BODY()
public:

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:

	void PerformAttackTrace(USkeletalMeshComponent* MeshComp);
	
	FTimerHandle TimerHandle_AttackTrace;
	
	TArray<AActor*> hitActors;

	class APunchPlayerCharacter* player;

	FName StartSocketName;
	FName objectivesTag;
	FVector startLocation;
	FVector endLocation;

	float amountOfDamage;
};
