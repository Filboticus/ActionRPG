// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerControllerBase.generated.h"

/** Forward Declarations */
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
struct FInputActionValue;


/** Base class for PlayerController, should be blueprinted */
UCLASS()
class ACTIONRPG_API ARPGPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	// Constructor
	ARPGPlayerControllerBase();
	
	virtual void PlayerTick(float DeltaTime) override;

protected:
	// Overrides
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category= "EnhancedInput")
	TObjectPtr<UInputMappingContext> RPGCharacterInputMappingContext;

	UPROPERTY(EditAnywhere, Category= "EnhancedInput")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category= "EnhancedInput")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, Category= "EnhancedInput")
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditAnywhere, Category= "EnhancedInput")
	TObjectPtr<UInputAction> MouseLeftClickAction;

	UPROPERTY(EditAnywhere, Category= "EnhancedInput")
	TObjectPtr<UInputAction> FaceTargetAction;
	
	void Move(const FInputActionValue& InputActionValue);

	void Look(const FInputActionValue& InputActionValue);

	void Zoom(const FInputActionValue& InputActionValue);

	void OnMouseLeftClick(const FInputActionValue& InputActionValue);

	void FaceTarget(const FInputActionValue& InputActionValue);

	void CursorTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	UPROPERTY()
	AActor* CurrentTarget; 
	
	
};
