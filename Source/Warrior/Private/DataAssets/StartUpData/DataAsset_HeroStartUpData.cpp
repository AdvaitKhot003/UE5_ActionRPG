// No Copyright


#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "Components/AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InAscToGive, ApplyLevel);

	for (const FWarriorHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InAscToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		
		InAscToGive->GiveAbility(AbilitySpec);
	}
}
