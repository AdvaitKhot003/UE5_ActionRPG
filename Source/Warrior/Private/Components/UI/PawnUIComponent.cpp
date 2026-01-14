// No Copyright


#include "Components/UI/PawnUIComponent.h"

void UPawnUIComponent::HandleHealthChanged(float NewHealth, float MaxHealth)
{
	const float HealthPercent = MaxHealth > 0.f ? NewHealth / MaxHealth : 0.f;
	OnHealthChanged.Broadcast(HealthPercent);
}
