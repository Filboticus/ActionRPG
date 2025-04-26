// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "RPGPlayerState.generated.h"

class URPGCombatSet;
class URPGHealthSet;
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class ACTIONRPG_API ARPGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARPGPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	URPGHealthSet* GetHealthSet() const;
	URPGCombatSet* GetCombatSet() const;

private:

	UPROPERTY(VisibleAnywhere, Category = "RPG|PlayerState")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	// Health attribute set used by this actor.
	UPROPERTY()
	TObjectPtr<URPGHealthSet> HealthSet;

	// Combat Attribute set used by this actor.
	UPROPERTY()
	TObjectPtr<URPGCombatSet> CombatSet;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

};
