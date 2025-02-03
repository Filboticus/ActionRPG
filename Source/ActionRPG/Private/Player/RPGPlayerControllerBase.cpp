// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RPGPlayerControllerBase.h"


#include "ComponentSourceInterfaces.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/RPGCharacter.h"
#include "Interaction/EnemyInterface.h"

ARPGPlayerControllerBase::ARPGPlayerControllerBase()
{
	bReplicates = true;
}

void ARPGPlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace(); 
}

void ARPGPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	// Check to see if InputMappingContext is Valid
	check(RPGCharacterInputMappingContext);

	// Get Local Player Subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{ 
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(RPGCharacterInputMappingContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ARPGPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Get EnhancedInputComponent
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Bind Move() to MoveAction
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGPlayerControllerBase::Move);

	// Bind Look() to LookAction
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARPGPlayerControllerBase::Look);

	// Bind Zoom() to ZoomAction
	EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ARPGPlayerControllerBase::Zoom);

	// Bind OnMouseLeftClick() to MouseLeftClickAction
	EnhancedInputComponent->BindAction(MouseLeftClickAction, ETriggerEvent::Triggered, this, &ARPGPlayerControllerBase::OnMouseLeftClick);

	// Bind FaceTargetAction() to FaceTargetAction
	EnhancedInputComponent->BindAction(FaceTargetAction, ETriggerEvent::Triggered, this, &ARPGPlayerControllerBase::FaceTarget);
}

void ARPGPlayerControllerBase::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	
}

void ARPGPlayerControllerBase::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(InputAxisVector.X);
		ControlledPawn->AddControllerPitchInput(InputAxisVector.Y);
	}
}

void ARPGPlayerControllerBase::Zoom(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Scroll Wheel - Zoom Function"));

	const float InputValue = InputActionValue.Get<float>();

	const APawn* MyPawn = GetPawn();
	
	if (MyPawn != nullptr)
	{
		USpringArmComponent* SpringArm = MyPawn->FindComponentByClass<USpringArmComponent>();
		
		UE_LOG(LogTemp, Warning, TEXT("Found Spring Arm Component: %s"), *SpringArm->GetName());

		const float NewTargetArmLength = SpringArm->TargetArmLength + InputValue * 45;
		SpringArm->TargetArmLength = FMath::Clamp(NewTargetArmLength, 200, 1000);
	}
}

void ARPGPlayerControllerBase::OnMouseLeftClick(const FInputActionValue& InputActionValue)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	//PreviousTarget = CurrentTarget;
	
	if (HitResult.bBlockingHit)
	{
		//Handle the click on the target
		
		AActor* TargetActor = HitResult.GetActor();
		CurrentTarget = TargetActor;

		if (TargetActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Target Actor: %s"), *TargetActor->GetName());
			
			// Highlight Actor
			ThisActor = TargetActor;
			if(ThisActor != nullptr)
			{
				ThisActor->HighlightActor();
			}
		}
	}
}

void ARPGPlayerControllerBase::FaceTarget(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Warning, TEXT("FaceTarget()"));

	if (CurrentTarget != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FaceTarget"));
	}
}

void ARPGPlayerControllerBase::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if(!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;

	ThisActor = CursorHit.GetActor();

	/**
	 * Line trace from cursor. There are several scenarios:
	 * A. LastActor is null && ThisActor is null
	 *		- Do Nothing
	 * B. LastActor is null && ThisActor is valid
	 *		- Hightlight ThisActor
	 * C. LastActor is valid && ThisActor is null
	 *		- UnHighlight LastActor
	 * D. LastActor is valid && ThisActor is valid, but LastActor != ThisActor
	 *		- UnHightlight LastActor, and Hightlight ThisActor
	 * E. LastActor is valid && ThisActor is valid, and LastActor == ThisActor
	 *		- Do Nothing
	 */

	 if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			/** Case B.  LastActor is null && ThisActor is valid
			*		- Hightlight this Actor	*/

			//ThisActor->HighlightActor();
		}
		else
		{
			/** A. LastActor is null && ThisActor is null
			*		- Do Nothing */
		}
	} 
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			/** C. LastActor is valid && ThisActor is null
			*		- UnHighlight LastActor	*/

			//LastActor->UnHighlightActor();
		}
		else // LastActor && ThisActor are valid
		{
			if (LastActor != ThisActor)
			{
				/** D. LastActor is valid && ThisActor is valid, but LastActor != ThisActor
				*		- UnHightlight LastActor, and Hightlight ThisActor */

				//LastActor->UnHighlightActor();

				//ThisActor->HighlightActor();
			}
			else
			{
				/** E. LastActor is valid && ThisActor is valid, and LastActor == ThisActor
				*		- Do Nothing */
			}
		}
	} 
}
