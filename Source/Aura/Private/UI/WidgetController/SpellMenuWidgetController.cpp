// Copyright Votive Game Studio


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"


void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	
	// Broadcast initial player state values
	SpellPointsChangedDelegate.Broadcast(GetAuraPlayerState()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraAbilitySystemComponent()->AbilityStatusChanged.AddLambda(
		[this](const FGameplayTag& AbilityTag, const FGameplayTag& NewStatusTag, const int32 NewAbilityLevel)
		{
			if (SelectedAbility.AbilityTag.MatchesTagExact(AbilityTag))
			{
				SelectedAbility.StatusTag = NewStatusTag;
				bool bEnableSpendPointsButton = false;
				bool bEnableEquipButton = false;
				
				ShouldEnableButtons(NewStatusTag, GetAuraPlayerState()->GetSpellPoints(), bEnableSpendPointsButton, bEnableEquipButton);
				
				FString Description;
				FString NextLevelDescription;
				GetAuraAbilitySystemComponent()->GetDescriptionsByAbilityTag(AbilityTag, NewAbilityLevel, Description, NextLevelDescription);
				
				SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPointsButton, bEnableEquipButton, Description, NextLevelDescription);
			}
			if (AbilityInfo)
			{
				FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
				Info.StatusTag = NewStatusTag;
				Info.Level = NewAbilityLevel;
				AbilityInfoDelegate.Broadcast(Info);
			}
		}	
	);
	
	GetAuraPlayerState()->OnSpellPointsChangedDelegate.AddLambda(
		[this](const int32 SpellPoints)
		{
			SpellPointsChangedDelegate.Broadcast(SpellPoints);
			CurrentSpellPoints = SpellPoints;
			bool bEnableSpendPointsButton = false;
			bool bEnableEquipButton = false;
			ShouldEnableButtons(SelectedAbility.StatusTag, CurrentSpellPoints, bEnableSpendPointsButton, bEnableEquipButton);
			
			FString Description;
			FString NextLevelDescription;
			int32 AbilityLevel = 0;
			if (const FGameplayAbilitySpec* AbilitySpec = GetAuraAbilitySystemComponent()->GetSpecFromAbilityTag(SelectedAbility.AbilityTag))
			{
				AbilityLevel = AbilitySpec->Level;
			}
			GetAuraAbilitySystemComponent()->GetDescriptionsByAbilityTag(SelectedAbility.AbilityTag, AbilityLevel, Description, NextLevelDescription);
			
			SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPointsButton, bEnableEquipButton, Description, NextLevelDescription);
		}	
	);
}

void USpellMenuWidgetController::SelectAbility(UAuraUserWidget* AbilityButton) const
{
	AbilitySelectedDelegate.Broadcast(AbilityButton);
}

void USpellMenuWidgetController::GetButtonStatusForAbility(const FGameplayTag& AbilityTag)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();	
	const int32 SpellPoints = GetAuraPlayerState()->GetSpellPoints();
	FGameplayTag AbilityStatus;	
	
	const FGameplayAbilitySpec* AbilitySpec = GetAuraAbilitySystemComponent()->GetSpecFromAbilityTag(AbilityTag);
	
	if (!AbilityTag.IsValid() || !AbilitySpec)
	{
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus = GetAuraAbilitySystemComponent()->GetStatusFromSpec(*AbilitySpec);
	}

	SelectedAbility.AbilityTag = AbilityTag;
	SelectedAbility.StatusTag = AbilityStatus;
	
	bool bEnableSpendPointsButton = false;
	bool bEnableEquipButton = false;
	
	ShouldEnableButtons(AbilityStatus, SpellPoints, bEnableSpendPointsButton, bEnableEquipButton);
	
	FString Description;
	FString NextLevelDescription;
	int32 AbilityLevel = 0;
	if (AbilitySpec) AbilityLevel = AbilitySpec->Level;
	
	GetAuraAbilitySystemComponent()->GetDescriptionsByAbilityTag(AbilityTag, AbilityLevel, Description, NextLevelDescription);
				
	SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPointsButton, bEnableEquipButton, Description, NextLevelDescription);
}

void USpellMenuWidgetController::SpendPointButtonPressed()
{
	if (GetAuraAbilitySystemComponent())
	{
		AuraAbilitySystemComponent->ServerSpendSpellPoint(SelectedAbility.AbilityTag);
		GetButtonStatusForAbility(SelectedAbility.AbilityTag);
	}
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, const int32 SpellPoints,
                                                     bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	const bool bHasSpellPoints = SpellPoints > 0;

	bShouldEnableSpellPointsButton = false;
	bShouldEnableEquipButton = false;
	
	if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
	{
		bShouldEnableSpellPointsButton = bHasSpellPoints;
		bShouldEnableEquipButton = true;
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		bShouldEnableSpellPointsButton = bHasSpellPoints;
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bShouldEnableSpellPointsButton = bHasSpellPoints;
		bShouldEnableEquipButton = true;
	}
}

