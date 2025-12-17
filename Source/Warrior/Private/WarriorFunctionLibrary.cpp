// No Copyright


#include "WarriorFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"

UWarriorAbilitySystemComponent* UWarriorFunctionLibrary::NativeGetWarriorAscFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UWarriorAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InGameplayTagToAdd)
{
	UWarriorAbilitySystemComponent* WarriorAsc = NativeGetWarriorAscFromActor(InActor);

	if (!WarriorAsc->HasMatchingGameplayTag(InGameplayTagToAdd))
	{
		WarriorAsc->AddLooseGameplayTag(InGameplayTagToAdd);
	}
}

void UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag InGameplayTagToRemove)
{
	UWarriorAbilitySystemComponent* WarriorAsc = NativeGetWarriorAscFromActor(InActor);

	if (WarriorAsc->HasMatchingGameplayTag(InGameplayTagToRemove))
	{
		WarriorAsc->RemoveLooseGameplayTag(InGameplayTagToRemove);
	}
}

bool UWarriorFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTagToCheck)
{
	UWarriorAbilitySystemComponent* WarriorAsc = NativeGetWarriorAscFromActor(InActor);

	return WarriorAsc->HasMatchingGameplayTag(InGameplayTagToCheck);
}

void UWarriorFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTagToCheck, EWarriorConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, InGameplayTagToCheck) ? EWarriorConfirmType::Yes : EWarriorConfirmType::No;
}
