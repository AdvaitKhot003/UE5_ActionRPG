// No Copyright


#include "WarriorGameplayTags.h"

namespace WarriorGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipAxe, "InputTag.EquipAxe");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipAxe, "InputTag.UnequipAxe");

	/** Event Tags **/
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_Equip_Axe, "PlayerTag.Event.Equip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_Unequip_Axe, "PlayerTag.Event.Unequip.Axe");

	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Weapon_Axe, "PlayerTag.Weapon.Axe");
}
