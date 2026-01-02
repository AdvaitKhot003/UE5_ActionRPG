// No Copyright


#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "Components/AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InAscToGive, ApplyLevel);

	GrantHeroStartUpAbilities(HeroStartUpAbilitySets, InAscToGive, ApplyLevel);
}

void UDataAsset_HeroStartUpData::GrantHeroStartUpAbilities(const TArray<FWarriorHeroAbilitySet>& InHeroStartUpAbilitySets,
	UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel)
{
	if (InHeroStartUpAbilitySets.IsEmpty())
	{
		return;
	}
	
	for (const FWarriorHeroAbilitySet& AbilitySet : InHeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InAscToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		
		InAscToGive->GiveAbility(AbilitySpec);
	}
}
