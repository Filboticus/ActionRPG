// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/RPGCombatSet.h"

#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/RPGAttributeSet.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RPGCombatSet)

class FLifetimeProperty;


URPGCombatSet::URPGCombatSet()
	: BaseDamage(0.0f)
	, BaseHeal(0.0f)
	, Power(35.0f)
	, MaxPower (100.0f)
	, Endurance(65.0f)
	, MaxEndurance(100.0f)
{
}

void URPGCombatSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(URPGCombatSet, BaseDamage, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGCombatSet, BaseHeal, COND_OwnerOnly, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(URPGCombatSet, Power, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGCombatSet, MaxPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGCombatSet, Endurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGCombatSet, MaxEndurance, COND_None, REPNOTIFY_Always);
}

void URPGCombatSet::OnRep_BaseDamage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGCombatSet, BaseDamage, OldValue);
}

void URPGCombatSet::OnRep_BaseHeal(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGCombatSet, BaseHeal, OldValue);
}

void URPGCombatSet::OnRep_Power(const FGameplayAttributeData& OldPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGCombatSet, Power, OldPower);
}

void URPGCombatSet::OnRep_MaxPower(const FGameplayAttributeData& OldMaxPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGCombatSet, MaxPower, OldMaxPower);
}

void URPGCombatSet::OnRep_Endurance(const FGameplayAttributeData& OldEndurance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGCombatSet, Endurance, OldEndurance);
}

void URPGCombatSet::OnRep_MaxEndurance(const FGameplayAttributeData& OldMaxEndurance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGCombatSet, MaxEndurance, OldMaxEndurance);
}

void URPGCombatSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void URPGCombatSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void URPGCombatSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetPowerAttribute())
	{
		// Do not allow Power to go negative or above Max Power
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxPower());
	}
	else if (Attribute == GetMaxPowerAttribute())
	{
		// Do not allow Max Power to drop below 0
		NewValue = FMath::Max(NewValue, 0.0f);
	}

	if (Attribute == GetEnduranceAttribute())
	{
		// Do not allow Endurance to go negative or above Max Endurance
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxEndurance());
	}
	else if (Attribute == GetMaxEnduranceAttribute())
	{
		// Do not allow Max Endurance to drop below 0
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}




