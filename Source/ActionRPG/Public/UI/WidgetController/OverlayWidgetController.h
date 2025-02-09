// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "UI/WidgetController/RPGWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPowerChangedSignature, float, NewPower);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxPowerChangedSignature, float, NewMaxPower);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnduranceChangedSignature, float, NewEndurance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxEnduranceChangedSignature, float, NewMaxEndurance);

/**
 * UOverlayWidgetController
 *
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ACTIONRPG_API UOverlayWidgetController : public URPGWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnPowerChangedSignature OnPowerChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnMaxPowerChangedSignature OnMaxPowerChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnEnduranceChangedSignature OnEnduranceChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnMaxEnduranceChangedSignature OnMaxEnduranceChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void PowerChanged(const FOnAttributeChangeData& Data) const;
	void MaxPowerChanged(const FOnAttributeChangeData& Data) const;
	void EnduranceChanged(const FOnAttributeChangeData& Data) const;
	void MaxEnduranceChanged(const FOnAttributeChangeData& Data) const;
	
};
