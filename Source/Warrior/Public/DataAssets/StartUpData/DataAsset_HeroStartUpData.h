// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_HeroStartUpData.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData", meta = (TitleProperty = "InputTag", AllowPrivateAccess = "true"))
	TArray<FWarriorHeroAbilitySet> HeroStartUpAbilitySets;

	void GrantHeroStartUpAbilities(const TArray<FWarriorHeroAbilitySet>& InHeroStartUpAbilitySets,
		UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1);
};
