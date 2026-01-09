// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UWarriorEnemyGameplayAbility;

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UWarriorEnemyGameplayAbility>> EnemyCombatAbilities;

	void GrantEnemyCombatAbilities(const TArray<TSubclassOf<UWarriorEnemyGameplayAbility>>& InEnemyCombatAbilities,
		UWarriorAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1);
};
