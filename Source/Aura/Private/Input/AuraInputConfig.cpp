// Copyright Guedert Games


#include "Input/AuraInputConfig.h"
#include "InputAction.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
    for (const FAuraInputAction& Action : AbilityInputActions)
    {
        if (IsValid(Action.InputAction) && Action.InputTag == InputTag)
        {
            return Action.InputAction;
        }
    }

    if (bLogNotFound)
    {
        UE_LOG(LogTemp, Error, TEXT("Ability not found for tag [%s], on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
    }

    return nullptr;
}
