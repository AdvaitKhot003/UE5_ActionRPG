// No Copyright


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/WarriorHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "WarriorFunctionLibrary.h"

#include "WarriorDebugHelper.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTagToGet));
}

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::ResetLightAttackComboCount()
{
	CurrentLightAttackComboCount = 1;

	if (GetWorld()->GetTimerManager().IsTimerActive(LightAttackComboResetTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(LightAttackComboResetTimerHandle);
	}
}

void UHeroCombatComponent::ResetHeavyAttackComboCount()
{
	CurrentHeavyAttackComboCount = 1;

	if (GetWorld()->GetTimerManager().IsTimerActive(HeavyAttackComboResetTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(HeavyAttackComboResetTimerHandle);
	}
}

void UHeroCombatComponent::OnWeaponEquipped(AActor* InActor, FGameplayTag InGameplayTagToRemove)
{
	if (!InActor)
	{
		return;
	}
	
	ResetLightAttackComboCount();
	ResetHeavyAttackComboCount();
	UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfFound(InActor, InGameplayTagToRemove);
}

void UHeroCombatComponent::OnWeaponBeginHitTargetActor(AActor* HitBeginActor)
{
	//Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" Begin Overlap With ") + HitBeginActor->GetActorNameOrLabel(), FColor::Green);
	
	if (OverlappedActors.Contains(HitBeginActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitBeginActor);

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitBeginActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(), WarriorGameplayTags::SharedTag_Event_MeleeHit, EventData);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(), WarriorGameplayTags::PlayerTag_Event_HitPause, EventData);
}

void UHeroCombatComponent::OnWeaponEndHitTargetActor(AActor* HitEndActor)
{
	//Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" End Overlap With ") + HitEndActor->GetActorNameOrLabel(), FColor::Red);
	
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitEndActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(), WarriorGameplayTags::PlayerTag_Event_HitPause, EventData);
}

void UHeroCombatComponent::StartHitPause(float RealTimeDuration, float TimeDilation)
{
	if (!GetWorld())
	{
		return;
	}

	RealTimeDuration = FMath::Clamp(RealTimeDuration, 0.005f, 0.1f);
	TimeDilation = FMath::Clamp(TimeDilation, 0.02f, 1.f);

	// Prevent stacking hit pauses
	GetWorld()->GetTimerManager().ClearTimer(HitPauseTimerHandle);

	// Apply time dilation immediately
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeDilation);

	// Start real time timer
	GetWorld()->GetTimerManager().SetTimer(
		HitPauseTimerHandle,
		this,
		&UHeroCombatComponent::EndHitPause,
		RealTimeDuration,
		false
	);
}

void UHeroCombatComponent::EndHitPause()
{
	if (!GetWorld())
	{
		return;
	}

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}
