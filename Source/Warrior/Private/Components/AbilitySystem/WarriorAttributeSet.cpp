// No Copyright


#include "Components/AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"

#include "WarriorDebugHelper.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitHealth(1.f);
	InitMaxHealth(1.f);
	InitRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UWarriorAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float NewHealth = FMath::Clamp(GetHealth(), 0.f, GetMaxHealth());
		SetHealth(NewHealth);
	}

	if (Data.EvaluatedData.Attribute == GetRageAttribute())
	{
		const float NewRage = FMath::Clamp(GetRage(), 0.f, GetMaxRage());
		SetRage(NewRage);
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetHealth();
		const float DamageDone = GetDamageTaken();
		const float NewHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetHealth(NewHealth);

		const FString DebugMessage = FString::Printf(
			TEXT("OldHealth: %f, DamageDone: %f, NewHealth: %f"), OldHealth, DamageDone, NewHealth);

		Debug::Print(DebugMessage, FColor::Green);

		if (NewHealth == 0.f)
		{
			UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(),
				WarriorGameplayTags::SharedTag_Status_IsDead);
		}
	}
}
