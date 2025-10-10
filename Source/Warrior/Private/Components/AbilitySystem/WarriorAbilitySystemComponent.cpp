// Copyright Advait Khot


#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Components/AbilitySystem/Abilities/WarriorGameplayAbility.h"

void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}
	
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;
		
		const UWarriorGameplayAbility* WarriorGameplayAbility = Cast<UWarriorGameplayAbility>(AbilitySpec.Ability);
		if (!WarriorGameplayAbility) continue;

		if (WarriorGameplayAbility->AbilityActivationPolicy != EWarriorAbilityActivationPolicy::OnTriggered) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UWarriorAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	
}
