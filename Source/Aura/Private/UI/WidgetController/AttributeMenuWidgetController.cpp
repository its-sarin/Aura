// Copyright Votive Studios


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AuraAttributeInfo.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo)
	
	// Broadcast all attribute values mapped in the attribute set
	for (TTuple<FGameplayTag, FGameplayAttribute(*)()>& TagAttributePair : GetAuraAttributeSet()->TagsToAttributes)
	{
		BroadcastAttributeInfo(TagAttributePair.Key, TagAttributePair.Value());
	}
	
	// Broadcast initial player state values
	AttributePointsChangedDelegate.Broadcast(GetAuraPlayerState()->GetAttributePoints());
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo)
		
	// Bind to attribute change delegates for all attributes mapped in the attribute set
	for (TTuple<FGameplayTag, FGameplayAttribute(*)()>& TagAttributePair : GetAuraAttributeSet()->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TagAttributePair.Value()).AddLambda(
			[this, TagAttributePair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(TagAttributePair.Key, TagAttributePair.Value());
			}	
		);
	}
	
	// Bind to player state delegates
	GetAuraPlayerState()->OnAttributePointsChangedDelegate.AddLambda(
		[this](const int32 AttributePoints)
		{
			AttributePointsChangedDelegate.Broadcast(AttributePoints);
		}	
	);
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	GetAuraAbilitySystemComponent()->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	// Get attribute info for the tag
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	// Get the attribute value
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	// Broadcast the attribute info
	AttributeInfoDelegate.Broadcast(Info);
}
