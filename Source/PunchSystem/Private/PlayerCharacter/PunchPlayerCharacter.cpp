


#include "PunchSystem/Public/PlayerCharacter/PunchPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


APunchPlayerCharacter::APunchPlayerCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);
	springArm->bUsePawnControlRotation = true;
	springArm->TargetArmLength = 400.0f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(springArm);
	FollowCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void APunchPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = GetMesh()->GetAnimInstance();
	if(APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* localPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			localPlayerSubsystem->AddMappingContext(InputMappingContext,0);
		}
	}
}

void APunchPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APunchPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	enhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&APunchPlayerCharacter::Move);
	enhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&APunchPlayerCharacter::Look);
	
	enhancedInputComponent->BindAction(AttackAction,ETriggerEvent::Started,this,&APunchPlayerCharacter::Attack);
}

void APunchPlayerCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	
}

void APunchPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2d input = Value.Get<FVector2d>();

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0,rotation.Yaw,0);

	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(forwardDirection,input.Y);
	AddMovementInput(rightDirection,input.X);
}

void APunchPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2d input = Value.Get<FVector2d>();

	AddControllerYawInput(input.X);
	AddControllerPitchInput(input.Y * -1);
}

void APunchPlayerCharacter::Attack()
{
	if(!AnimInstance)
	{
		return;
	}
	if(!AnimInstance->IsAnyMontagePlaying() || bAttackCombo)
	{
		if(bDoOnce)
		{
			damageInfo.DamageType = E_DamageType::Melee;
			damageInfo.DeathType = E_DeathType::Melee;
			damageInfo.AttackWay = comboCount;
			damageInfo.AmountOfDamage = 10.0f;
			CurrentAttackMontage = AttackMontages[comboCount];
			AnimInstance->Montage_Play(CurrentAttackMontage);
			bDoOnce = false;
			UGameplayStatics::PlaySoundAtLocation(GetWorld(),punchSound,GetActorLocation());
			AnimInstance->OnMontageEnded.AddDynamic(this,&APunchPlayerCharacter::OnMontageEnded);
		}
	}
}

void APunchPlayerCharacter::AttackComboContinue()
{
	bAttackCombo = true;
	bDoOnce = true;
	comboCount++;
	if(comboCount > AttackMontages.Num()-1)
	{
		comboCount = 0;
	}
}

void APunchPlayerCharacter::AttackComboEnd()
{
	bDoOnce = true;
	bAttackCombo = false;
	comboCount = 0;
}



