// No Copyright


#include "Components/AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"
#include "WarriorGameplayTags.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"

AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedWarriorHeroCharacter.IsValid())
	{
		CachedWarriorHeroCharacter = Cast<AWarriorHeroCharacter>(GetCurrentActorInfo()->AvatarActor);
	}
	return CachedWarriorHeroCharacter.IsValid()? CachedWarriorHeroCharacter.Get() : nullptr;
}

AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedWarriorHeroController.IsValid())
	{
		CachedWarriorHeroController = Cast<AWarriorHeroController>(GetCurrentActorInfo()->PlayerController);
	}
	return CachedWarriorHeroController.IsValid()? CachedWarriorHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	if (const AWarriorHeroCharacter* HeroCharacter = GetHeroCharacterFromActorInfo())
	{
		return HeroCharacter->GetHeroCombatComponent();
	}
	return nullptr;
}

FGameplayEffectSpecHandle UWarriorHeroGameplayAbility::MakeHeroDamageGameplayEffectSpecHandle(
	TSubclassOf<UGameplayEffect> GameplayEffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag,
	int32 InCachedComboCount)
{
	check(GameplayEffectClass);

	UWarriorAbilitySystemComponent* WarriorAsc = GetWarriorAbilitySystemComponentFromActorInfo();
	check(WarriorAsc);

	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	AActor* WeaponActor = nullptr;
	UObject* WeaponSourceObject = nullptr;

	if (UHeroCombatComponent* HeroCombatComponent = GetHeroCombatComponentFromActorInfo())
	{
		// Keep the original object for SourceObject
		WeaponSourceObject = HeroCombatComponent->GetCharacterCurrentEquippedWeapon();

		// Only use as EffectCauser if it's actually an Actor
		WeaponActor = Cast<AActor>(WeaponSourceObject);
	}

	FGameplayEffectContextHandle ContextHandle = WarriorAsc->MakeEffectContext();
	ContextHandle.SetAbility(this);

	// SourceObject = extra context (weapon, data asset, etc.)
	if (WeaponSourceObject)
	{
		ContextHandle.AddSourceObject(WeaponSourceObject);
	}

	// Instigator = character, EffectCauser = weapon if valid, else character
	ContextHandle.AddInstigator(AvatarActor, WeaponActor ? WeaponActor : AvatarActor);

	FGameplayEffectSpecHandle GameplayEffectSpecHandle =
		WarriorAsc->MakeOutgoingSpec(GameplayEffectClass, GetAbilityLevel(), ContextHandle);

	if (GameplayEffectSpecHandle.IsValid())
	{
		GameplayEffectSpecHandle.Data->SetSetByCallerMagnitude(
			WarriorGameplayTags::SharedTag_SetByCaller_BaseDamage, InWeaponBaseDamage);

		if (InCurrentAttackTypeTag.IsValid())
		{
			GameplayEffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InCachedComboCount);
		}
	}

	return GameplayEffectSpecHandle;
}
