// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorGameplayAbility;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;

	void GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive,
		UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1);

	void ApplyStartUpGameplayEffects(const TArray<TSubclassOf<UGameplayEffect>>& InGameplayEffectsToApply,
		UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1);
};
