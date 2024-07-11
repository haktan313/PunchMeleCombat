


#include "PlayerCharacter/AnimNotifyState_PunchTrace.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerCharacter/PunchPlayerCharacter.h"
#include "StatSystem/Interface_StatSystem.h"

void UAnimNotifyState_PunchTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,float TotalDuration)
{
	if(MeshComp && MeshComp->GetOwner())
	{
		player = Cast<APunchPlayerCharacter>(MeshComp->GetOwner());
		if(player)
		{
			int punchInt = player->comboCount;
			StartSocketName = player->AttackSocketNames[punchInt];
			MeshComp->GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackTrace, FTimerDelegate::CreateUObject(this, &UAnimNotifyState_PunchTrace::PerformAttackTrace, MeshComp), 0.001f, true);
		}
	}
}

void UAnimNotifyState_PunchTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(MeshComp && MeshComp->GetOwner())
	{
		MeshComp->GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AttackTrace);
		hitActors.Empty();
	}
}

void UAnimNotifyState_PunchTrace::PerformAttackTrace(USkeletalMeshComponent* MeshComp)
{
	startLocation = MeshComp->GetSocketLocation(StartSocketName);
	endLocation = startLocation + (UKismetMathLibrary::GetForwardVector(MeshComp->GetSocketRotation(StartSocketName)) * 18.f);
	const float radius = 8.f;
	TArray<FHitResult> hitResults;

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(MeshComp->GetOwner());

	UKismetSystemLibrary::SphereTraceMulti(MeshComp->GetWorld(),startLocation,endLocation,radius,
	UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1),false,ignoreActors,EDrawDebugTrace::None, hitResults,true,FLinearColor::Red,FLinearColor::Green,5.f);

	for(const FHitResult& hit : hitResults)
	{
		AActor* hitActor = hit.GetActor();
		if(hitActor && !hitActors.Contains(hitActor))
		{
			hitActors.Add(hitActor);
			if(hitActor->ActorHasTag("Enemy"))
			{
				IInterface_StatSystem::Execute_TakeDamage(hitActor,player->damageInfo);
			}
		}
	}
}
