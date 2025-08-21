// Copyright Guedert Games


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"
#include "Character/AuraCharacter.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = CurrentActor;
	CurrentActor = CursorHit.GetActor();

	/**
	* Line trace from cursor. There are several scenarios:
	*	A. LastActor is null && CurrentActor is null
	*		- Do nothing.
	*	B. LastActor is null && CurrentActor is valid
	*		- Highlight CurrentActor.
	*	C. LastActor is valid && CurrentActor is null
	*		- UnHighlight LastActor.
	*	D. Both actors are valid, but LastActor != CurrentActor
	*		- UnHighlight LastActor, and Highlight CurrentActor
	*	E. Both actors are valid, and are the same actor
	*		- Do nothing.
	*/

	if (LastActor == nullptr)
	{
		if (CurrentActor != nullptr)
		{
			//Case B
			CurrentActor->HighlightActor();
		}
		else
		{
			//Case A - both are null, do nothing
		}
	}
	else //LastActor is valid
	{
		if (CurrentActor == nullptr)
		{
			//Case C
			LastActor->UnHighlightActor();
		}
		else //both actors are valid
		{
			if (LastActor != CurrentActor)
			{
				//Case D
				LastActor->UnHighlightActor();
				CurrentActor->HighlightActor();
			}
			else
			{
				//Case E - Do nothing
			}
		}
	}

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//On a Topdown game the forward direction is the direction from the camera to the character as if it was leveled to the ground
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
