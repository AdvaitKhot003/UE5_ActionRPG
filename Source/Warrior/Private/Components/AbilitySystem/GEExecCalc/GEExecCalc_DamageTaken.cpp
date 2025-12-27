// No Copyright


#include "Components/AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "Components/AbilitySystem/WarriorAttributeSet.h"
#include "WarriorGameplayTags.h"

#include "WarriorDebugHelper.h"

struct FWarriorDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);

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
	Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);

	float BaseDamage = OwningGESpec.GetSetByCallerMagnitude(
		WarriorGameplayTags::SharedTag_SetByCaller_BaseDamage, false, 0.f);
	Debug::Print(TEXT("BaseDamage"), BaseDamage);

	const float CachedLightAttackComboCount = OwningGESpec.GetSetByCallerMagnitude(
		WarriorGameplayTags::PlayerTag_SetByCaller_AttackType_Light, false, 0.f);
	Debug::Print(TEXT("CachedLightAttackComboCount"), CachedLightAttackComboCount);

	const float CachedHeavyAttackComboCount = OwningGESpec.GetSetByCallerMagnitude(
		WarriorGameplayTags::PlayerTag_SetByCaller_AttackType_Heavy, false, 0.f);
	Debug::Print(TEXT("CachedHeavyAttackComboCount"), CachedHeavyAttackComboCount);
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		GetWarriorDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

	if (CachedHeavyAttackComboCount > 0.f)
	{
		const float HeavyAttackComboMultiplier = 1.5f + (CachedHeavyAttackComboCount - 1.f) * 0.5f;

		BaseDamage *= HeavyAttackComboMultiplier;
		Debug::Print(TEXT("BaseDamageHeavyAttack"), BaseDamage);
	}
	else if (CachedLightAttackComboCount > 0.f)
	{
		const float LightAttackComboMultiplier = 1.0f + (CachedLightAttackComboCount - 1.f) * 0.25f;

		BaseDamage *= LightAttackComboMultiplier;
		Debug::Print(TEXT("BaseDamageLightAttack"), BaseDamage);
	}

	const float FinalDamageDone = BaseDamage * (SourceAttackPower / (SourceAttackPower + TargetDefensePower));
	Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);

	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			UWarriorAttributeSet::GetDamageTakenAttribute(), EGameplayModOp::Override, FinalDamageDone));
	}
}
