// No Copyright


#include "Components/AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"
#include "WarriorGameplayTags.h"

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
	if (AWarriorHeroCharacter* HeroCharacter = GetHeroCharacterFromActorInfo())
	{
		return HeroCharacter->GetHeroCombatComponent();
	}
	return nullptr;
}


FGameplayEffectSpecHandle UWarriorHeroGameplayAbility::MakeHeroDamageGameplayEffectSpecHandle(TSubclassOf<UGameplayEffect> GameplayEffectClass,
	float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCachedComboCount)
{
	check(GameplayEffectClass);
	
	UWarriorAbilitySystemComponent* WarriorAsc = GetWarriorAbilitySystemComponentFromActorInfo();
	check(WarriorAsc);

	FGameplayEffectContextHandle ContextHandle = WarriorAsc->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = WarriorAsc->MakeOutgoingSpec(GameplayEffectClass, GetAbilityLevel(), ContextHandle);

	if (EffectSpecHandle.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(WarriorGameplayTags::SharedTag_SetByCaller_BaseDamage, InWeaponBaseDamage);

		if (InCurrentAttackTypeTag.IsValid())
		{
			EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InCachedComboCount);
		}
	}

	return EffectSpecHandle;
}
