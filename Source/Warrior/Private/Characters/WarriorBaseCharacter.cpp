// No Copyright


#include "Characters/WarriorBaseCharacter.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Components/AbilitySystem/WarriorAttributeSet.h"

AWarriorBaseCharacter::AWarriorBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
	GetMesh()->BoundsScale = 3.f;

	WarriorAbilitySystemComponent = CreateDefaultSubobject<UWarriorAbilitySystemComponent>("WarriorAbilitySystemComponent");
	WarriorAttributeSet = CreateDefaultSubobject<UWarriorAttributeSet>("WarriorAttributeSet");
}

UAbilitySystemComponent* AWarriorBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWarriorAbilitySystemComponent();
}

UPawnCombatComponent* AWarriorBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

void AWarriorBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (WarriorAbilitySystemComponent)
	{
		WarriorAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpDataAsset.IsNull(),
			TEXT("Warning: TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpDataAsset is nullptr in PossessedBy in WarriorBaseCharacter."));
	}
}
