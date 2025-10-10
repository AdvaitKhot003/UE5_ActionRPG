// Copyright Advait Khot


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FWarriorInputActionConfig& NativeInputActionConfig : NativeInputActions)
	{
		if (NativeInputActionConfig.InputTag == InInputTag && NativeInputActionConfig.InputAction)
		{
			return NativeInputActionConfig.InputAction;
		}
	}
	return nullptr;
}
