


#include "StatSystem/StatSystemComponent.h"
#include "StatSystem/Structure_StatSystem.h"


void UStatSystemComponent::TakeDamage(FS_DamageInfo aboutDamage)
{
	if(bIsDead)
	{
		return;
	}
	if(currentHealth > 0)
	{
		currentHealth -= aboutDamage.AmountOfDamage;
		if(currentHealth <= 0)
		{
			currentHealth = 0;
			bIsDead = true;
			OnDeath.Broadcast(aboutDamage.DeathType,aboutDamage.AttackWay);
		}
		else
		{
			OnDamageResponse.Broadcast(aboutDamage.DamageType,aboutDamage.AttackWay);
		}
	}
}

