// No Copyright


#include "WarriorFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"

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

UPawnCombatComponent* UWarriorFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);
	
	if (const IPawnCombatInterface* PawnCombatInterface= Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	
	return nullptr;
}

UPawnCombatComponent* UWarriorFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EWarriorValidType& OutValidType)
{
	UPawnCombatComponent* PawnCombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	OutValidType = PawnCombatComponent ? EWarriorValidType::Valid : EWarriorValidType::Invalid;
	return PawnCombatComponent;
}

bool UWarriorFunctionLibrary::IsTargetPawnHostile(const APawn* QueryPawn, const APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);
	
	const IGenericTeamAgentInterface* QueryAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	const IGenericTeamAgentInterface* TargetAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryAgent && TargetAgent)
	{
		return QueryAgent->GetGenericTeamId() != TargetAgent->GetGenericTeamId();
	}
	return false;
}
