// Copyright Votive Studios


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AuraAttributeInfo.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo)
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	
	// Broadcast all attribute values mapped in the attribute set
	for (auto& TagAttributePair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(TagAttributePair.Key, TagAttributePair.Value());
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo)
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	
	// Bind to attribute change delegates for all attributes mapped in the attribute set
	for (auto& TagAttributePair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TagAttributePair.Value()).AddLambda(
			[this, TagAttributePair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(TagAttributePair.Key, TagAttributePair.Value());
			}	
		);
	}
	
	// Bind to player state delegates
	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 AttributePoints)
		{
			AttributePointsChangedDelegate.Broadcast(AttributePoints);
		}	
	);
	AuraPlayerState->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 SpellPoints)
		{
			SpellPointsChangedDelegate.Broadcast(SpellPoints);
		}	
	);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	// Get attribute info for the tag
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	// Get the attribute value
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	// Broadcast the attribute info
	AttributeInfoDelegate.Broadcast(Info);
}
