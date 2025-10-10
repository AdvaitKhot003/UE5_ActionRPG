// Copyright Advait Khot

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAssets/StartUpData/DataAsset_BaseStartUpData.h"
#include "DataAsset_HeroStartUpData.generated.h"

class UWarriorGameplayAbility;

USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWarriorGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_HeroStartUpData : public UDataAsset_BaseStartUpData
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FWarriorHeroAbilitySet> HeroStartUpAbilitySets;
};
