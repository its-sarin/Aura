// Copyright Votive Game Studio


#include "AbilitySystem/Data/LevelUpInfo.h"


int32 ULevelUpInfo::FindLevelForXP(const int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;
	
	while (bSearching)
	{
		// LevelUpInformation[0] is simply an empty placeholder
		// LevelUpInformation[1] = Level 1 information
		// LevelUpInformation[2] = Level 2 information, etc
		// Therefore if LevelUpInformation.Num() - 1 <= Level, 
		// then we have reached the end of the array and should return the current level
		if (LevelUpInformation.Num() - 1 <= Level) return Level;
		
		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	
	return Level;
}
