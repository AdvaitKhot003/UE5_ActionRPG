// No Copyright


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/WarriorHeroWeapon.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTagToGet));
}

void UHeroCombatComponent::ResetLightAttackComboCount()
{
	CurrentLightAttackComboCount = 1;

	if (GetWorld()->GetTimerManager().IsTimerActive(LightComboCountResetTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(LightComboCountResetTimerHandle);
	}
}
