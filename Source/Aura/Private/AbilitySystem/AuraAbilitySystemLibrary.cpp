// Copyright Guedert Games


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/AuraHUD.h"
#include "Player/AuraPlayerState.h"
#include "UI/WidgetControllers/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!IsValid(PC))
	{
		return nullptr;
	}

	AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
	if (!IsValid(AuraHUD))
	{
		return nullptr;
	}

	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	if (!IsValid(PS))
	{
		return nullptr;
	}

	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS = PS->GetAttributeSet();
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

	return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!IsValid(PC))
	{
		return nullptr;
	}

	AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
	if (!IsValid(AuraHUD))
	{
		return nullptr;
	}

	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	if (!IsValid(PS))
	{
		return nullptr;
	}

	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS = PS->GetAttributeSet();
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

	return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
}
