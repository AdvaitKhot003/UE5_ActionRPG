// No Copyright


#include "Components/AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "Components/AbilitySystem/WarriorAttributeSet.h"
#include "WarriorGameplayTags.h"

struct FWarriorDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)

	FWarriorDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DefensePower, Target, false);
	}
};

static const FWarriorDamageCapture& GetWarriorDamageCapture()
{
	static FWarriorDamageCapture WarriorDamageCapture;
	return WarriorDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DefensePowerDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& OwningGESpec = ExecutionParams.GetOwningSpec();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = OwningGESpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = OwningGESpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		GetWarriorDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	const float BaseDamage =
		OwningGESpec.GetSetByCallerMagnitude(
			WarriorGameplayTags::SharedTag_SetByCaller_BaseDamage, false, 0.f);

	const float CachedLightAttackComboCount =
		OwningGESpec.GetSetByCallerMagnitude(
			WarriorGameplayTags::PlayerTag_SetByCaller_AttackType_Light, false, 0.f);

	const float CachedHeavyAttackComboCount =
		OwningGESpec.GetSetByCallerMagnitude(
			WarriorGameplayTags::PlayerTag_SetByCaller_AttackType_Heavy, false, 0.f);
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		GetWarriorDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
}
