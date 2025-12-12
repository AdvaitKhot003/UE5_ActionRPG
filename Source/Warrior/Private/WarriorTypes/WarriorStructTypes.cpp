// No Copyright


#include "WarriorTypes/WarriorStructTypes.h"
#include "Components/AbilitySystem/Abilities/WarriorGameplayAbility.h"

bool FWarriorHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
