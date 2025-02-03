// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RPGCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/RPGPlayerControllerBase.h"
#include "Player/RPGPlayerState.h"
#include "UI/HUD/RPGHUD.h"

ARPGCharacter::ARPGCharacter()
{
	/** Instantiating Class Components */

	// Create Spring Arm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	// Attach the Spring Arm to the Root Component
	SpringArmComponent->SetupAttachment(RootComponent);
	
	// Create and attach camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	// Set default properties of the SpringArmComponent
	
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->TargetArmLength = 600.f;

	// CharacterMovement Settings
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	// Pawn Settings
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
}

void ARPGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability Actor Info for the Server
	InitAbilityActorInfo();
	
}

void ARPGCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability Actor Info for the Client
	InitAbilityActorInfo();
}

void ARPGCharacter::InitAbilityActorInfo()
{
	ARPGPlayerState* RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	RPGPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(RPGPlayerState, this);
	AbilitySystemComponent = RPGPlayerState->GetAbilitySystemComponent();
	AttributeSet = RPGPlayerState->GetAttributeSet();

	if (ARPGPlayerControllerBase* RPGPlayerControllerBase = Cast<ARPGPlayerControllerBase>(GetController())) //TODO Should I rename RPGPlayerControllerBase to RPGPlayerController?
	{
		if (ARPGHUD* RPGHUD = Cast<ARPGHUD>(RPGPlayerControllerBase->GetHUD()))
		{
			RPGHUD->InitOverlay(RPGPlayerControllerBase, RPGPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
