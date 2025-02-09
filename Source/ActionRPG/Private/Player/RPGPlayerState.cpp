// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RPGPlayerState.h"

#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/RPGAttributeSet.h"
#include "AbilitySystem/Attributes/RPGCombatSet.h"
#include "AbilitySystem/Attributes/RPGHealthSet.h"

ARPGPlayerState::ARPGPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// These ATTRIBUTE SETS will be detected by AbilitySystemComponent::InitializeComponent. Keeping a reference so that the sets don't get garbage collected before that.
	HealthSet = CreateDefaultSubobject<URPGHealthSet>(TEXT("HealthSet"));
	CombatSet = CreateDefaultSubobject<URPGCombatSet>(TEXT("CombatSet")); 

	// AbilitySystemComponent needs to be updated at a high frequency.
	NetUpdateFrequency = 100.f; //How often the server tries to update the clients
}

UAbilitySystemComponent* ARPGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

URPGHealthSet* ARPGPlayerState::GetHealthSet() const
{
	return HealthSet;
}

URPGCombatSet* ARPGPlayerState::GetCombatSet() const
{
	return CombatSet;
}
