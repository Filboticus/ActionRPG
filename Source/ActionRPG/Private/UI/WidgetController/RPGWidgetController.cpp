// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/RPGWidgetController.h"

void URPGWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	HealthSet = WCParams.HealthSet;
	CombatSet = WCParams.CombatSet;
}

void URPGWidgetController::BroadcastInitialValues()
{
	// Override function in classes that derive RPGWidgetController
}

void URPGWidgetController::BindCallbacksToDependencies()
{
	// Override function in classes that derive RPGWidgetController
}
