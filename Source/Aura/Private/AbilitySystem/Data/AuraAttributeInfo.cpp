// Copyright Votive Studios


#include "AbilitySystem/Data/AuraAttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Info not found for tag [%s] on AttributeInfo [%s]"), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	
	return FAuraAttributeInfo();
}

void UAttributeInfo::UpdateAttributeInformation()
{
	
}
