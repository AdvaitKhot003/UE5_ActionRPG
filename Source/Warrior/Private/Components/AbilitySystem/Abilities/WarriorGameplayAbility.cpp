// No Copyright


#include "Components/AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/Combat/PawnCombatComponent.h"

void UWarriorGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UWarriorGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UWarriorGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UWarriorAbilitySystemComponent* UWarriorGameplayAbility::GetWarriorAbilitySystemComponentFromActorInfo() const
{
	return Cast<UWarriorAbilitySystemComponent>(GetCurrentActorInfo()->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UWarriorGameplayAbility::NativeApplyGESpecHandleToTargetActor(AActor* TargetActor,
	const FGameplayEffectSpecHandle& GameplayEffectSpecHandle)
{
	UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	UWarriorAbilitySystemComponent* SourceAsc = GetWarriorAbilitySystemComponentFromActorInfo();
	check(TargetAsc);
	check(SourceAsc);
	check(GameplayEffectSpecHandle.IsValid());
	return SourceAsc->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(), TargetAsc);
}

FActiveGameplayEffectHandle UWarriorGameplayAbility::BP_ApplyGESpecHandleToTargetActor(AActor* TargetActor,
	const FGameplayEffectSpecHandle& GameplayEffectSpecHandle, EWarriorSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyGESpecHandleToTargetActor(TargetActor, GameplayEffectSpecHandle);
	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied()?
		EWarriorSuccessType::Successful : EWarriorSuccessType::Failed;
	
	return ActiveGameplayEffectHandle;
}
