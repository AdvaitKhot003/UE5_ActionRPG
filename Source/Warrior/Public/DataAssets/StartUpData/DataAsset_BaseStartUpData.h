// Copyright Advait Khot

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_BaseStartUpData.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorGameplayAbility;

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_BaseStartUpData : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAscToGive, const int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive,
		UWarriorAbilitySystemComponent* InAscToGive, const int32 ApplyLevel = 1);
};
