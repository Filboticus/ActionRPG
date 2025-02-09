// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Executions/RPGDamageExecution.h"

URPGDamageExecution::URPGDamageExecution()
{
	
}

void URPGDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
}
