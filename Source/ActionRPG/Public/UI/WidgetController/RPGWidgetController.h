// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/Attributes/RPGCombatSet.h"
#include "AbilitySystem/Attributes/RPGHealthSet.h"
#include "UObject/NoExportTypes.h"
#include "RPGWidgetController.generated.h"

class URPGCombatSet;
class URPGAttributeSet;
class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, URPGHealthSet* HAS, URPGCombatSet* CAS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), HealthSet(HAS), CombatSet(CAS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<URPGHealthSet> HealthSet = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<URPGCombatSet> CombatSet = nullptr;
};

/**
 * Get data from "Model/System, ie: ability system component, attribute set, character, etc" and BROADCAST to widgets
 *
 * PlayerController, PlayerState, AbilitySystemComponent, AttributeSet
 */
UCLASS()
class ACTIONRPG_API URPGWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	virtual void BroadcastInitialValues();

	virtual void BindCallbacksToDependencies();
	
protected:
	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TObjectPtr<URPGHealthSet> HealthSet;

	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TObjectPtr<URPGCombatSet> CombatSet;

	
};
