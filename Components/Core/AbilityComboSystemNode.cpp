// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Core/AbilityComboSystemNode.h"
#include "../../GAS/AbilityConditions/AbilityConditionFunctor.h"

FAbilityComboSystemLink UAbilityComboSystemNode::GetBestLink(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
{
	for (const FAbilityComboSystemLink& IteratedLink : Links)
	{
		bool bAllSucceed = true;
		for (const UAbilityConditionFunctor* IteratedFunctor : IteratedLink.Conditions)
		{
			if (IteratedFunctor->EvaluateCondition(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)  == false)
			{
				bAllSucceed = false;
				break;
			}
		}
		if (bAllSucceed)
		{
			return IteratedLink;
		}
	}

	return FAbilityComboSystemLink();
}

TSet<UInputAction*> UAbilityComboSystemNode::GetInputActions_Implementation() const 
{
	TSet<UInputAction*> OutActions;

	for (const FAbilityComboSystemLink& IteratedLink : Links)
	{
		for (const UAbilityConditionFunctor* IteratedCondition : IteratedLink.Conditions)
		{
			if (IteratedCondition->GetClass()->ImplementsInterface(UInputBindingsInterface::StaticClass()))
			{
				OutActions.Append(IInputBindingsInterface::Execute_GetInputActions(IteratedCondition));
			}
		}
	}

	return OutActions;
}
