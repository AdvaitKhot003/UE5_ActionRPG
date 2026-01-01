// No Copyright


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FWarriorInputActionConfig& NativeInputActionConfig : NativeInputActions)
	{
		if (NativeInputActionConfig.IsValid() && NativeInputActionConfig.InputTag == InInputTag)
		{
			return NativeInputActionConfig.InputAction;
		}
	}
	return nullptr;
}
