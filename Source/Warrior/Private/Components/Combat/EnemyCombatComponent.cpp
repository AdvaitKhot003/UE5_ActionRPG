// No Copyright


#include "Components/Combat/EnemyCombatComponent.h"

#include "WarriorDebugHelper.h"

void UEnemyCombatComponent::OnWeaponBeginHitTargetActor(AActor* HitBeginActor)
{
	if (HitBeginActor)
	{
		Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" Begin Overlap with ") + HitBeginActor->GetName(), FColor::Green);
	}
}

void UEnemyCombatComponent::OnWeaponEndHitTargetActor(AActor* HitEndActor)
{
	if (HitEndActor)
	{
		Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" End Overlap with ") + HitEndActor->GetName(), FColor::Red);
	}
}
