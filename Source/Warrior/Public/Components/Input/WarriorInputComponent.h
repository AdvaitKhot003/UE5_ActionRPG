// Copyright Advait Khot

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarriorInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunction>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunction Function);

	template<class UserObject, typename CallbackFunction>
	void BindAbilityInputAction (const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject,
		CallbackFunction InputPressedFunction, CallbackFunction InputReleasedFunction);
};

template <class UserObject, typename CallbackFunction>
void UWarriorInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunction Function)
{
	checkf(InInputConfig, TEXT("InInputConfig is null, cannot proceed with the binding"));

	if (UInputAction* FoundInputAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundInputAction, TriggerEvent, ContextObject, Function);
	}
}

template <class UserObject, typename CallbackFunction>
void UWarriorInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig,
	UserObject* ContextObject, CallbackFunction InputPressedFunction, CallbackFunction InputReleasedFunction)
{
	checkf(InInputConfig, TEXT("InInputConfig is null, cannot proceed with the binding"));

	for (const FWarriorInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunction,
			AbilityInputActionConfig.InputTag);
		
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunction,
			AbilityInputActionConfig.InputTag);
	}
}
