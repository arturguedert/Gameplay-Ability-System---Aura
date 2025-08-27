// Copyright Guedert Games


#include "Character/AuraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	if (UCharacterMovementComponent* CharacterMovementComp = GetCharacterMovement())
	{
		CharacterMovementComp->bOrientRotationToMovement = true;
		CharacterMovementComp->RotationRate = FRotator(0.f, 400.f, 0.f);
		CharacterMovementComp->bConstrainToPlane = true;
		CharacterMovementComp->bSnapToPlaneAtStart = true;

		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;
		bUseControllerRotationYaw = false;
	}
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init ability actor for Server
	InitAbilityInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability actor for Client
	InitAbilityInfo();
}

void AAuraCharacter::InitAbilityInfo()
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	if (IsValid(AuraPS))
	{
		AbilitySystemComponent = AuraPS->GetAbilitySystemComponent();
		AttributeSet = AuraPS->GetAttributeSet();
	}

	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(AuraPS, this);
	}
	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		AuraASC->AbilityActorInfoSet();
	}

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!IsValid(PlayerController))
	{
		return;
	}
	AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD());
	if (IsValid(AuraHUD))
	{
		AuraHUD->InitOverlay(PlayerController, AuraPS, AbilitySystemComponent, AttributeSet);
	}

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
}
