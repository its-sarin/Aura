// Copyright Votive Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
class UAbilitySystemComponent;
class UAttributeSet;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*NewValue*/);

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
	
	/**
	 * Player Level 
	 */
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FOnPlayerStatChanged OnLevelChangedDelegate;
	void SetLevel(const int32 InLevel);
	void AddToLevel(const int32 InLevel);
	
	/**
	 * Player XP 
	 */
	FORCEINLINE int32 GetPlayerXP() const { return XP; }
	FOnPlayerStatChanged OnXPChangedDelegate;
	void SetXP(const int32 InXP);
	void AddToXP(const int32 InXP);
	
	/**
	 * Attribute Points 
	 */
	FORCEINLINE int32 GetAttributePoints() const { return AttributePoints; }
	FOnPlayerStatChanged OnAttributePointsChangedDelegate;
	void SetAttributePoints(const int32 InAttributePoints);
	void AddToAttributePoints(const int32 InAttributePoints);
	
	/**
	 * Spell Points 
	 */
	FORCEINLINE int32 GetSpellPoints() const { return SpellPoints; }
	FOnPlayerStatChanged OnSpellPointsChangedDelegate;
	void SetSpellPoints(const int32 InSpellPoints);
	void AddToSpellPoints(const int32 InSpellPoints);
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
private:
	/**
	 * Player Level 
	 */
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
	
	/**
	 * Player XP 
	 */
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int32 XP = 0;
	
	UFUNCTION()
	void OnRep_XP(int32 OldXP);
	
	/**
	 * Attribute Points 
	 */
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_AttributePoints)
	int32 AttributePoints = 0;
	
	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);
	
	/**
	 * Spell Points 
	 */
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_SpellPoints)
	int32 SpellPoints = 0;
	
	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);
};
