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

	InWeaponToRegister->OnWeaponBeginHitTarget.BindUObject(this, &ThisClass::OnWeaponBeginHitTargetActor);
	InWeaponToRegister->OnWeaponEndHitTarget.BindUObject(this, &ThisClass::OnWeaponEndHitTargetActor);

	if (bRegisteredAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}

	/** const FString WeaponString = FString::Printf(TEXT("A weapon named %s is registered with a tag named %s"),
		*InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString());
	
	Debug::Print(WeaponString, FColor::Green); **/
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
		AWarriorWeaponBase* WeaponToToggleCollision = GetCharacterCurrentEquippedWeapon();

		if (!WeaponToToggleCollision)
		{
			return;
		}

		if (bShouldEnableCollision)
		{
			WeaponToToggleCollision->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
			//Debug::Print(WeaponToToggleCollision->GetName() + TEXT(" is now colliding with other actors"), FColor::Green);
		}
		else
		{
			WeaponToToggleCollision->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
			//Debug::Print(WeaponToToggleCollision->GetName() + TEXT(" is no longer colliding with other actors"), FColor::Red);

			OverlappedActors.Empty();
		}
	}
}

void UPawnCombatComponent::OnWeaponBeginHitTargetActor(AActor* HitBeginActor)
{
	
}

void UPawnCombatComponent::OnWeaponEndHitTargetActor(AActor* HitEndActor)
{
	
}
