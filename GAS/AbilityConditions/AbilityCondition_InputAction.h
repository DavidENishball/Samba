// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/AbilityConditions/AbilityConditionFunctor.h"
#include "Interfaces/InputBindingsInterface.h"
#include "AbilityCondition_InputAction.generated.h"

/**
 * A functor that evaluates that the owner is a player character and a particular key is pressed or not pressed.
 */
UCLASS()
class SAMBA_API UAbilityCondition_InputAction : public UAbilityConditionFunctor, public IInputBindingsInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UInputAction* Action;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bPressed = true;

	virtual bool EvaluateCondition(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const override; 

	
	// Begin IInputBindingsInterface
	virtual TSet<UInputAction*> GetInputActions_Implementation() const;
	// End IInputBindingsInterface

protected:
	// Begin UObject Interface
	EDataValidationResult IsDataValid(FDataValidationContext& ValidationErrors) const override;
	// End UObject Interface
};
