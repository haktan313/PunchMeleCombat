


#include "Enemys/EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "StatSystem/StatSystemComponent.h"


AEnemyBase::AEnemyBase()
{
	Tags.Add(FName("Enemy"));
	PrimaryActorTick.bCanEverTick = true;

	StatSystemComponent = CreateDefaultSubobject<UStatSystemComponent>(TEXT("StatSystemComponent"));

}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	bIsDead = StatSystemComponent->bIsDead;
	AnimInstance = GetMesh()->GetAnimInstance();
	if (StatSystemComponent)
	{
		StatSystemComponent->OnDeath.AddDynamic(this, &AEnemyBase::DeathResponse);
		StatSystemComponent->OnDamageResponse.AddDynamic(this, &AEnemyBase::DamageResponse);
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if(NotifyName == "Dead")
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
		GetMesh()->SetSimulatePhysics(true);
		GetCapsuleComponent()->DestroyComponent();
		AnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &AEnemyBase::OnNotifyBegin);
	}
}

void AEnemyBase::TakeDamage_Implementation(FS_DamageInfo aboutDamage)
{
	StatSystemComponent->TakeDamage(aboutDamage);
}

void AEnemyBase::DamageResponse(E_DamageType damageType, int AttackWay)
{
	if(!AnimInstance)
	{
		return;
	}
	UGameplayStatics::PlaySound2D(GetWorld(),damageSound);
	UGameplayStatics::PlayWorldCameraShake(GetWorld(),damageCameraShake, GetActorLocation(),150.f,600.f,2.f,true);
	switch (damageType)
	{
	case E_DamageType::Melee:
		if(meleeDamageMontage.Num() > 0)
		{
			AnimInstance->Montage_Play(meleeDamageMontage[AttackWay]);
			break;
		}
	}
}

void AEnemyBase::DeathResponse(E_DeathType deathType, int AttackWay)
{
	if(!AnimInstance)
	{
		return;
	}
	UGameplayStatics::PlaySound2D(GetWorld(),damageSound);
	UGameplayStatics::PlayWorldCameraShake(GetWorld(),damageCameraShake, GetActorLocation(),150.f,600.f,2.f,true);
	switch (deathType)
	{
	case E_DeathType::Melee:
		if(meleeDeathMontage.Num() > 0)
		{
			AnimInstance->Montage_Play(meleeDeathMontage[AttackWay]);
			break;
		}
	}
	AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AEnemyBase::OnNotifyBegin);
}

