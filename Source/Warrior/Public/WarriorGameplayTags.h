// No Copyright

#pragma once

#include "NativeGameplayTags.h"

namespace WarriorGameplayTags
{
	/** Input Tags **/
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttackAxe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttackAxe);

	/** Ability Tags **/
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Ability_Equip_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Ability_Unequip_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Ability_LightAttack_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Ability_HeavyAttack_Axe);

	/** Event Tags **/
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Event_Equip_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Event_Unequip_Axe);

	/** Weapon Tags **/
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Weapon_Axe);

	/** State Tags **/
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_State_WeaponTransition);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_State_Attacking);

	/** Status Tags **/
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Status_JumpToFinisher);

	/** Enemy Weapon Tags **/
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(EnemyTag_Weapon);
}
