// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilityConditionFunctor.generated.h"


/**
 * A function object that can be compared to an ability activation and provide a boolean result.  
 * This allows us to compose conditions dynamically by context.
 */
UCLASS(ABSTRACT, BlueprintType, Blueprintable, DefaultToInstanced, editinlinenew)
class SAMBA_API UAbilityConditionFunctor : public UObject
{
	GENERATED_BODY()
public:
	virtual bool EvaluateCondition(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const;  // Copied from GameplayAbility::CanActivateAbility.

	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName="EvaluateCondition", meta=(ScriptName="EvaluateCondition"))
	bool K2_EvaluateCondition(FGameplayAbilityActorInfo ActorInfo, const FGameplayAbilitySpecHandle Handle, FGameplayTagContainer& RelevantTags) const;
};
