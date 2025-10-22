// No Copyright


#include "DataAssets/Input//DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FWarriorInputActionConfig& NativeInputActionConfig : NativeInputActions)
	{
		if (NativeInputActionConfig.InputTag == InInputTag && NativeInputActionConfig.IsValid())
		{
			return NativeInputActionConfig.InputAction;
		}
	}
	return nullptr;
}
