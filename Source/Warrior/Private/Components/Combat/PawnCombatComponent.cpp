// No Copyright


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"
#include "Components/BoxComponent.h"

#include "WarriorDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeaponByTag(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister,
	bool bRegisteredAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister),
		TEXT("CharacterCarriedWeaponMap already contains a tag named %s"), *InWeaponTagToRegister.ToString());

	checkf(InWeaponToRegister, TEXT("In RegisterSpawnedWeaponByTag Function InWeaponToRegister is nullptr"));

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if (bRegisteredAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}

	const FString WeaponString = FString::Printf(TEXT("A weapon named %s is registered with a tag named %s"),
		*InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString());
	Debug::Print(WeaponString, FColor::Green);
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}
	return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnableCollision, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AWarriorWeaponBase* WeaponCollisionToToggle = GetCharacterCurrentEquippedWeapon();

		if (!WeaponCollisionToToggle)
		{
			return;
		}

		if (bShouldEnableCollision)
		{
			WeaponCollisionToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
			Debug::Print(WeaponCollisionToToggle->GetName() + TEXT(" Collision Enabled"), FColor::Green);
		}
		else
		{
			WeaponCollisionToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
			Debug::Print(WeaponCollisionToToggle->GetName() + TEXT(" Collision Disabled"), FColor::Red);
		}
	}
}
