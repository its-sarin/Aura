// Copyright Votive Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
class UAbilitySystemComponent;
class UAttributeSet;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChangedSignature, int32 /* NewXP or NewLevel */);

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
	FOnPlayerStatChangedSignature OnLevelChangedDelegate;
	void SetLevel(const int32 InLevel);
	void AddLevel(const int32 InLevel);
	
	/**
	 * Player XP 
	 */
	FORCEINLINE int32 GetPlayerXP() const { return XP; }
	FOnPlayerStatChangedSignature OnXPChangedDelegate;
	void SetXP(const int32 InXP);
	void AddXP(const int32 InXP);
	
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
};
