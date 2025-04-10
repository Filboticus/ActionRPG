// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/RPGAttributeSet.h"

#include "RPGCombatSet.generated.h"

class UObject;
struct FFrame;

/**
 * URPGCombatSet
 *
 *	Class that defines attributes that are necessary for applying damage or healing.
 *	Attribute examples include: damage, healing, attack power, and shield penetrations.
 */
UCLASS(BlueprintType)
class ACTIONRPG_API URPGCombatSet : public URPGAttributeSet
{
	GENERATED_BODY()

public:

	URPGCombatSet();

	ATTRIBUTE_ACCESSORS(URPGCombatSet, BaseDamage);
	ATTRIBUTE_ACCESSORS(URPGCombatSet, BaseHeal);
	ATTRIBUTE_ACCESSORS(URPGCombatSet, Power);
	ATTRIBUTE_ACCESSORS(URPGCombatSet, MaxPower);
	ATTRIBUTE_ACCESSORS(URPGCombatSet, Endurance);
	ATTRIBUTE_ACCESSORS(URPGCombatSet, MaxEndurance);
	

protected:

	UFUNCTION()
	void OnRep_BaseDamage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_BaseHeal(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Power(const FGameplayAttributeData& OldPower);

	UFUNCTION()
	void OnRep_MaxPower(const FGameplayAttributeData& OldMaxPower);
	
	UFUNCTION()
	void OnRep_Endurance(const FGameplayAttributeData& OldEndurance) const;

	UFUNCTION()
	void OnRep_MaxEndurance(const FGameplayAttributeData& OldMaxEndurance) const;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

	void CancelEnduranceRegen();

public:

private:

	// The base amount of damage to apply in the damage execution.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseDamage, Category = "RPG|Combat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseDamage;

	// The base amount of healing to apply in the heal execution.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseHeal, Category = "RPG|Combat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseHeal;

public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Power, Category= "RPG|Combat|Attributes")
	FGameplayAttributeData Power;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxPower, Category= "RPG|Combat|Attributes")
	FGameplayAttributeData MaxPower;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Endurance, Category= "RPG|Combat|Attributes")
	FGameplayAttributeData Endurance;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxEndurance, Category= "RPG|Combat|Attributes")
	FGameplayAttributeData MaxEndurance;
};
