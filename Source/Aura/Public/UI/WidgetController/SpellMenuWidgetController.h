// Copyright Votive Game Studio

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

class UAuraUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilitySelectedSignature, UAuraUserWidget*, AbilityButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FUpdateButtonSignature, bool, bSpendPointsButtonEnabled, bool, bEquipSpellButtonEnabled, FString, DescriptionString, FString, NextLevelDescriptionString);

// USTRUCT(BlueprintType)
// struct FButtonStatus
// {
// 	GENERATED_BODY()
// 	
// 	UPROPERTY(BlueprintReadOnly)
// 	bool bSpendPointButtonEnabled = false;
// 	
// 	UPROPERTY(BlueprintReadOnly)
// 	bool bEquipSpellButtonEnabled = false;
// 	
// };

struct FSelectedAbility
{
	FGameplayTag AbilityTag = FGameplayTag();
	FGameplayTag StatusTag = FGameplayTag();
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Spells Menu")
	FAbilitySelectedSignature AbilitySelectedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|SpellPoints")
	FOnPlayerStatChangedSignature SpellPointsChangedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|SpellPoints")
	FUpdateButtonSignature SpellGlobeSelectedDelegate;
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	UFUNCTION(BlueprintCallable, Category = "GAS|Spells Menu")
	void SelectAbility(UAuraUserWidget* AbilityButton) const;
	
	UFUNCTION(BlueprintCallable, Category = "GAS|Spells Menu")
	void GetButtonStatusForAbility(const FGameplayTag& AbilityTag);
	
	UFUNCTION(BlueprintCallable, Category = "GAS|Spells Menu")
	void SpendPointButtonPressed();
	
private:
	static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton);
	
	FSelectedAbility SelectedAbility = FSelectedAbility();
	int32 CurrentSpellPoints = 0;
};
