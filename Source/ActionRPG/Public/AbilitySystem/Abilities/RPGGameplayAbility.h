// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RPGGameplayAbility.generated.h"


class URPGAbilitySystemComponent;
class ARPGPlayerControllerBase;
class AController;
/**
 * URPGGameplayAbility
 *
 *  The base gameplay ability class used by this project. 
 */
UCLASS(Abstract, HideCategories = Input, Meta = (ShortToolTip = "The base gameplay ability class used by this project."))
class ACTIONRPG_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	friend class URPGAbilitySystemComponent;

public:

	URPGGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	
	UFUNCTION(BlueprintCallable, Category = "RPG|Ability")	
	URPGAbilitySystemComponent* GetRPGAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "RPG|Ability")
	ARPGPlayerControllerBase* GetRPGPlayerControllerBaseFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|Ability")
	AController* GetControllerFromActorInfo() const;
	
	
};
