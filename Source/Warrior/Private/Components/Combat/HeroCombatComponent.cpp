// No Copyright


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/WarriorHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"

#include "WarriorDebugHelper.h"

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

void UHeroCombatComponent::OnWeaponBeginHitTargetActor(AActor* HitBeginActor)
{
	if (OverlapedActors.Contains(HitBeginActor))
	{
		return;
	}

	OverlapedActors.AddUnique(HitBeginActor);

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitBeginActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(), WarriorGameplayTags::SharedTag_Event_MeleeHit, EventData);
}

void UHeroCombatComponent::OnWeaponEndHitTargetActor(AActor* HitEndActor)
{
	
}
