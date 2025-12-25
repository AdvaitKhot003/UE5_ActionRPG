// No Copyright


#include "WarriorGameplayTags.h"

namespace WarriorGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipAxe, "InputTag.EquipAxe");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipAxe, "InputTag.UnequipAxe");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttackAxe, "InputTag.LightAttackAxe");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttackAxe, "InputTag.HeavyAttackAxe");

	/** Ability Tags **/
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Equip_Axe, "PlayerTag.Ability.Equip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Unequip_Axe, "PlayerTag.Ability.Unequip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_LightAttack_Axe, "PlayerTag.Ability.LightAttack.Axe");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_HeavyAttack_Axe, "PlayerTag.Ability.HeavyAttack.Axe");

	/** Event Tags **/
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_Equip_Axe, "PlayerTag.Event.Equip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_Unequip_Axe, "PlayerTag.Event.Unequip.Axe");

	/** Shared Event Tags **/
	UE_DEFINE_GAMEPLAY_TAG(SharedTag_Event_MeleeHit, "SharedTag.Event.MeleeHit");

	/** Weapon Tags **/
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Weapon_Axe, "PlayerTag.Weapon.Axe");
	
	/** Enemy Weapon Tags **/
	UE_DEFINE_GAMEPLAY_TAG(EnemyTag_Weapon, "EnemyTag.Weapon");

	/** State Tags **/
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_State_WeaponTransition, "PlayerTag.State.WeaponTransition");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_State_Attacking, "PlayerTag.State.Attacking");

	/** Status Tags **/
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Status_JumpToFinisher, "PlayerTag.Status.JumpToFinisher");
}
