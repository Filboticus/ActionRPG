// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "RPGHealExecution.generated.h"

class UObject;

/**
 * URPGHealExecution
 *
 * Execution used by gameplay effects to apply healing to the health attributes.
 */
UCLASS()
class ACTIONRPG_API URPGHealExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	
	URPGHealExecution();

protected:

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
