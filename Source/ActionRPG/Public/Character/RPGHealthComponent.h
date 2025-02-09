// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"

#include "RPGHealthComponent.generated.h"

class URPGHealthComponent;

class URPGAbilitySystemComponent;
class URPGHealthSet;
struct FFrame;
struct FGameplayEffectSpec;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FRPGHealth_AttributeChanged, URPGHealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);

/**
 * URPGHealthComponent
 *
 *	An actor component used to handle anything related to health.
 */
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ACTIONRPG_API URPGHealthComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	URPGHealthComponent(const FObjectInitializer& ObjectInitializer);

	// Initialize the component using an ability system component.
	UFUNCTION(BlueprintCallable, Category = "RPG|Health")
	void InitializeWithAbilitySystem(URPGAbilitySystemComponent* InASC);

public:
	// Delegate fired when the health value has changed. This is called on the client but the instigator may not be valid
	UPROPERTY(BlueprintAssignable)
	FRPGHealth_AttributeChanged OnHealthChanged;

	// Delegate fired when the max health value has changed. This is called on the client but the instigator may not be valid
	UPROPERTY(BlueprintAssignable)
	FRPGHealth_AttributeChanged OnMaxHealthChanged;

protected:
	
	virtual void HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	virtual void HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	
protected:

	// Ability system used by this component.
	UPROPERTY()
	TObjectPtr<URPGAbilitySystemComponent> AbilitySystemComponent;

	// Health set used by this component.
	UPROPERTY()
	TObjectPtr<const URPGHealthSet> HealthSet;
	
};
