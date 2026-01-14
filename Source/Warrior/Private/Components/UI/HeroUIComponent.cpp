// No Copyright


#include "Components/UI/HeroUIComponent.h"

void UHeroUIComponent::HandleRageChanged(float NewRage, float MaxRage)
{
	const float RagePercent = MaxRage > 0.f ? NewRage / MaxRage : 0.f;
	OnRageChanged.Broadcast(RagePercent);
}
