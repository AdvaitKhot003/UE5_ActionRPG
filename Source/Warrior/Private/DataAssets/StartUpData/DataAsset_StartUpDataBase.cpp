// No Copyright


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Components/AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel)
{
	checkf(InAscToGive,
		TEXT("Warning: UWarriorAbilitySystemComponent* InAscToGive is nullptr in GiveToAbilitySystemComponent in DataAsset_StartUpDataBase."));

	GrantAbilities(ActivateOnGivenAbilities, InAscToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InAscToGive, ApplyLevel);
	ApplyStartUpGameplayEffects(StartUpGameplayEffects, InAscToGive, ApplyLevel);
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive,
	UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UWarriorGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InAscToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InAscToGive->GiveAbility(AbilitySpec);
	}
}

void UDataAsset_StartUpDataBase::ApplyStartUpGameplayEffects(const TArray<TSubclassOf<UGameplayEffect>>& InGameplayEffectsToApply,
	UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel)
{
	if (InGameplayEffectsToApply.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UGameplayEffect>& GameplayEffect : InGameplayEffectsToApply)
	{
		if (!GameplayEffect) continue;

		const UGameplayEffect* GameplayEffectCDO = GameplayEffect->GetDefaultObject<UGameplayEffect>();

		FGameplayEffectContextHandle ContextHandle = InAscToGive->MakeEffectContext();
		ContextHandle.AddSourceObject(InAscToGive->GetAvatarActor());

		InAscToGive->ApplyGameplayEffectToSelf(GameplayEffectCDO, ApplyLevel, ContextHandle);
	}
}
