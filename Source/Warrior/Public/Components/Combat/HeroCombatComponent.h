// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AWarriorHeroWeapon;

/**
 * 
 */
UCLASS()
class WARRIOR_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Warrior|Ability")
	int32 CurrentLightAttackComboCount = 1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Warrior|Ability")
	FTimerHandle LightComboCountResetTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	void ResetLightAttackComboCount();

	virtual void OnWeaponBeginHitTargetActor(AActor* HitBeginActor) override;
	virtual void OnWeaponEndHitTargetActor(AActor* HitEndActor) override;
};
