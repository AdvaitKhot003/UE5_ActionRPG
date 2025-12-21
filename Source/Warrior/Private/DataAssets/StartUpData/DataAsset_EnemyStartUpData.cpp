// No Copyright


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"
#include "Components/AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAscToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InAscToGive, ApplyLevel);

	if (EnemyCombatAbilities.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UWarriorEnemyGameplayAbility>& Ability : EnemyCombatAbilities)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InAscToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InAscToGive->GiveAbility(AbilitySpec);
	}
}
