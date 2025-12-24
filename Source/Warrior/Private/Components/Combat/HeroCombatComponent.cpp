// No Copyright


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/WarriorHeroWeapon.h"

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
	Debug::Print(
		GetOwningPawn()->GetActorNameOrLabel() + TEXT(" begin hit ") + HitBeginActor->GetActorNameOrLabel(),
		FColor::Green);
}

void UHeroCombatComponent::OnWeaponEndHitTargetActor(AActor* HitEndActor)
{
	Debug::Print(
		GetOwningPawn()->GetActorNameOrLabel() + TEXT(" end hit ") + HitEndActor->GetActorNameOrLabel(),
		FColor::Red);
}
