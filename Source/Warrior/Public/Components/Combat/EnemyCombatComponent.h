// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

	virtual void OnWeaponBeginHitTargetActor(AActor* HitBeginActor) override;
	virtual void OnWeaponEndHitTargetActor(AActor* HitEndActor) override;
};
