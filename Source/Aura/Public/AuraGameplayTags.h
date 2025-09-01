// Copyright Guedert Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 * 
 * Singleton Containing native GameplayTags
 */

struct FAuraGameplayTags
{
public: 
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	// Primary Attributes
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	// Secondary Attributes
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistence;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;

	//Vital Attributes
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;

protected:

private:
	static FAuraGameplayTags GameplayTags;
};