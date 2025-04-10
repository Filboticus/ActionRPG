// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "RPGCharacterBase.generated.h"

class URPGCombatSet;
class URPGHealthSet;
class URPGHealthComponent;
class UGameplayAbility;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract) 
class ACTIONRPG_API ARPGCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacterBase();

	UFUNCTION(BlueprintCallable, Category = "RPG|Character")
	URPGAbilitySystemComponent* GetRPGAbilitySystemComponent() const;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


private:

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon_Left;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URPGHealthComponent> HealthComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY()
	TObjectPtr<URPGHealthSet> HealthSet;

	UPROPERTY()
	TObjectPtr<URPGCombatSet> CombatSet;

protected:

	void AddCharacterAbilities();
	
private:
	
	UPROPERTY(EditAnywhere, Category= "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
