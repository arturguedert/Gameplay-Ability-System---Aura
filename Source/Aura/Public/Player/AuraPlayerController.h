// Copyright Guedert Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;
class USplineComponent;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UFUNCTION()
	void Move(const FInputActionValue& InputActionValue);

	void AutoRun();

	void CursorTrace();

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	void ShiftPressed() { bShiftKeyDown = true; };
	void ShiftReleased() { bShiftKeyDown = false; };
	bool bShiftKeyDown = false;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> CurrentActor;
	FHitResult CursorHit;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();

	UPROPERTY(EditDefaultsOnly, Category = "Click to Move")
	float ShortPressThreshold = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Click to Move")
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	bool bAutoRunning = false;
	bool bTargeting = false;
};
