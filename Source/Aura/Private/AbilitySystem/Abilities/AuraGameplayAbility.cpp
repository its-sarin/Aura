// Copyright Votive Studios


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

FString UAuraGameplayAbility::GetDescription(const int32 AbilityLevel)
{
	return FString::Printf(TEXT("%s, <Level>%d</>"), L"Default Ability Name - Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", AbilityLevel);
}

FString UAuraGameplayAbility::GetNextLevelDescription(const int32 AbilityLevel)
{
	return FString::Printf(TEXT("Next Level: <Level>%d</> \n Causes much more damage"), AbilityLevel);
}

FString UAuraGameplayAbility::GetLockedDescription(const int32 AbilityLevel)
{
	return FString::Printf(TEXT("Unlocks at Level <Level>%d</>"), AbilityLevel);
}
