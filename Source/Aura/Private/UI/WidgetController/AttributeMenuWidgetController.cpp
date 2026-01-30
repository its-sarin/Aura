// Copyright Votive Studios


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AuraAttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo)
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	
	// Broadcast all attribute values mapped in the attribute set
	for (auto& TagAttributePair : AS->TagsToAttributes)
	{
		// Get attribute info for the tag
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(TagAttributePair.Key);
		// Get the attribute value using the mapped function pointer
		Info.AttributeValue = TagAttributePair.Value().GetNumericValue(AS);
		// Broadcast the attribute info
		AttributeInfoDelegate.Broadcast(Info);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}
