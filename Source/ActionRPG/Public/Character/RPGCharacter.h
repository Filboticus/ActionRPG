// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Character/RPGCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "RPGCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API ARPGCharacter : public ARPGCharacterBase
{
	GENERATED_BODY()

public:

	ARPGCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:

	virtual void OnAbilitySystemInitialized();
	virtual void OnAbilitySystemUninitialized();
	
	void InitializeGameplayTags();

	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category= "Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category= "Camera")
	UCameraComponent* CameraComponent;

private:
	void InitAbilityActorInfo();
	
};
