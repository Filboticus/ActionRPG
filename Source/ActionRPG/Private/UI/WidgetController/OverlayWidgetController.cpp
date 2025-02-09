// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/Attributes/RPGAttributeSet.h"
#include "AbilitySystem/Attributes/RPGHealthSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	//const URPGAttributeSet* RPGAttributeSet = CastChecked<URPGAttributeSet>(AttributeSet);
	const URPGHealthSet* RPGHealthSet = CastChecked<URPGHealthSet>(HealthSet);
	const URPGCombatSet* RPGCombatSet = CastChecked<URPGCombatSet>(CombatSet);
	
	OnHealthChanged.Broadcast(RPGHealthSet->GetHealth());
	OnMaxHealthChanged.Broadcast(RPGHealthSet->GetMaxHealth());
	OnPowerChanged.Broadcast(RPGCombatSet->GetPower());
	OnMaxPowerChanged.Broadcast(RPGCombatSet->GetMaxPower());
	OnEnduranceChanged.Broadcast(RPGCombatSet->GetEndurance());
	OnMaxEnduranceChanged.Broadcast(RPGCombatSet->GetMaxEndurance());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	//const URPGAttributeSet* RPGAttributeSet = CastChecked<URPGAttributeSet>(AttributeSet);
	const URPGHealthSet* RPGHealthSet = CastChecked<URPGHealthSet>(HealthSet);
	const URPGCombatSet* RPGCombatSet = CastChecked<URPGCombatSet>(CombatSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RPGHealthSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RPGHealthSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RPGCombatSet->GetPowerAttribute()).AddUObject(this, &UOverlayWidgetController::PowerChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RPGCombatSet->GetMaxPowerAttribute()).AddUObject(this, &UOverlayWidgetController::MaxPowerChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RPGCombatSet->GetEnduranceAttribute()).AddUObject(this, &UOverlayWidgetController::EnduranceChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RPGCombatSet->GetMaxEnduranceAttribute()).AddUObject(this, &UOverlayWidgetController::MaxEnduranceChanged);

}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::PowerChanged(const FOnAttributeChangeData& Data) const
{
	OnPowerChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxPowerChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxPowerChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::EnduranceChanged(const FOnAttributeChangeData& Data) const
{
	OnEnduranceChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxEnduranceChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxEnduranceChanged.Broadcast(Data.NewValue);
}
