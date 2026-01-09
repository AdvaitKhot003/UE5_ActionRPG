// No Copyright


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"
#include "Components/AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAscToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InAscToGive, ApplyLevel);

	GrantEnemyCombatAbilities(EnemyCombatAbilities, InAscToGive, ApplyLevel);
}

void UDataAsset_EnemyStartUpData::GrantEnemyCombatAbilities(const TArray<TSubclassOf<UWarriorEnemyGameplayAbility>>& InEnemyCombatAbilities,
	UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel)
{
	if (InEnemyCombatAbilities.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UWarriorEnemyGameplayAbility>& Ability : InEnemyCombatAbilities)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InAscToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InAscToGive->GiveAbility(AbilitySpec);
	}
}
