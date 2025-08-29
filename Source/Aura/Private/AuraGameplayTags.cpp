// Copyright Guedert Games


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

//Creates a static object for this Singleton
FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secundary.Armor"), FString("Reduces damage taken, improves Block Chance"));
}
