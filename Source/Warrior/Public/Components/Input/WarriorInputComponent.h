// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input//DataAsset_InputConfig.h"
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
};

template <class UserObject, typename CallbackFunction>
void UWarriorInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunction Function)
{
	checkf(InInputConfig, TEXT("Warning: UDataAsset_InputConfig* InInputConfig is nullptr."));

	if (UInputAction* FoundInputAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundInputAction, TriggerEvent, ContextObject, Function);
	}
}
