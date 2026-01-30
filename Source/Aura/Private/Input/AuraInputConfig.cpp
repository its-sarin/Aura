// Copyright Votive Studios


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& AbilityInputAction : AbilityInputActions)
	{
		if (AbilityInputAction.InputAction && AbilityInputAction.InputTag.MatchesTagExact(InputTag))
		{
			return AbilityInputAction.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Info not found for InputTag [%s] on Input Config [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}
