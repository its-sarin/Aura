// Copyright Votive Studios

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Input/AuraInputConfig.h"
#include "AuraInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAuraInputComponent();
	
	template<class UserClass, typename PressedFuncType, typename HeldFuncType, typename ReleasedFuncType>
	void BindAbilityActions(class UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, HeldFuncType HeldFunc, ReleasedFuncType ReleasedFunc)
	{
		check(InputConfig);
		
		for (const FAuraInputAction& AbilityInputAction : InputConfig->AbilityInputActions)
		{
			if (!AbilityInputAction.InputAction || !AbilityInputAction.InputTag.IsValid()) continue;
			
			if (PressedFunc)
			{
				BindAction(AbilityInputAction.InputAction, ETriggerEvent::Started, Object, PressedFunc, AbilityInputAction.InputTag);
			}
			
			if (HeldFunc)
			{
				BindAction(AbilityInputAction.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, AbilityInputAction.InputTag);
			}
			
			if (ReleasedFunc)
			{
				BindAction(AbilityInputAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, AbilityInputAction.InputTag);
			}
		}
	}
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
