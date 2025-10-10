// Copyright Advait Khot


#include "DataAssets/StartUpData/DataAsset_BaseStartUpData.h"
#include "Components/AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"

void UDataAsset_BaseStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel)
{
	check(InAscToGive);

	GrantAbilities(ActivateOnGivenAbilities, InAscToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InAscToGive, ApplyLevel);
}

void UDataAsset_BaseStartUpData::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive,
	UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UWarriorGameplayAbility>& FoundAbility : InAbilitiesToGive)
	{
		if (!FoundAbility) continue;

		FGameplayAbilitySpec AbilitySpec(FoundAbility);
		AbilitySpec.SourceObject = InAscToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InAscToGive->GiveAbility(AbilitySpec);
	}
}
