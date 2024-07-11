


#include "PlayerCharacter/AnimNotify_AttackComboContinue.h"
#include "PlayerCharacter/PunchPlayerCharacter.h"

void UAnimNotify_AttackComboContinue::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(AActor* owner = MeshComp->GetOwner())
	{
		if(APunchPlayerCharacter* player = Cast<APunchPlayerCharacter>(owner))
		{
			player->AttackComboContinue();
		}
	}
}
