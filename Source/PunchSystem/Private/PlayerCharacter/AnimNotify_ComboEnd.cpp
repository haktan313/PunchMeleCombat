

#include "PlayerCharacter/AnimNotify_ComboEnd.h"
#include "PlayerCharacter/PunchPlayerCharacter.h"

void UAnimNotify_ComboEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(AActor* owner = MeshComp->GetOwner())
	{
		if(APunchPlayerCharacter* player = Cast<APunchPlayerCharacter>(owner))
		{
			player->AttackComboEnd();
		}
	}
}
