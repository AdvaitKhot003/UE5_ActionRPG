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

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorHeroWeapon* GetHeroCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Warrior|Ability")
	int32 CurrentLightAttackComboCount = 1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Warrior|Ability")
	FTimerHandle LightAttackComboResetTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Warrior|Ability")
	int32 CurrentHeavyAttackComboCount = 1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Warrior|Ability")
	FTimerHandle HeavyAttackComboResetTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	void ResetLightAttackComboCount();

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	void ResetHeavyAttackComboCount();

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	void OnWeaponEquipped(AActor* InActor, FGameplayTag InGameplayTagToRemove);

	virtual void OnWeaponBeginHitTargetActor(AActor* HitBeginActor) override;
	virtual void OnWeaponEndHitTargetActor(AActor* HitEndActor) override;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	void StartHitPause(float RealTimeDuration, float TimeDilation);

private:
	FTimerHandle HitPauseTimerHandle;

	void EndHitPause();
};
