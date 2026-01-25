// Copyright Votive Studios


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	for (const FGameplayTag& Tag : TagContainer)
	{
		// TODO: Broadcast the tag to the Widget Controller
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, FString::Printf(TEXT("Applied Game Effect with Tag: %s"), *Tag.ToString()));
	}
}
