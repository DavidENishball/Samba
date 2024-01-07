// Fill out your copyright notice in the Description page of Project Settings.

#define LOCTEXT_NAMESPACE "AbilityCondition_InputAction"
#include "GAS/AbilityConditions/AbilityCondition_InputAction.h"
#include "EnhancedInputComponent.h"

bool UAbilityCondition_InputAction::EvaluateCondition(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
{

	UInputComponent* FoundInputComponent = ActorInfo->AvatarActor->FindComponentByClass<UInputComponent>();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(FoundInputComponent))
	{
		// Problem: Actions count as Events, not Values.  No way to check statically?
		// I can, but I have to use BindActionValue instead of Bind Action.
		FInputActionValue FoundValue = EnhancedInputComponent->GetBoundActionValue(Action);
		float Magnitude = FoundValue.GetMagnitude();
		return ((Magnitude > 0) == bPressed);
	}

	return false;
	// TODO: Figure out how to handle this condition if it's an AI.
}


TSet<UInputAction*> UAbilityCondition_InputAction::GetInputActions_Implementation() const
{
	return TSet<UInputAction*>({ Action });
}

#if WITH_EDITOR
#include <Misc/DataValidation.h>
EDataValidationResult UAbilityCondition_InputAction::IsDataValid(FDataValidationContext& ValidationErrors) const
{
	EDataValidationResult Result = Super::IsDataValid(ValidationErrors);

	if (Action == nullptr)
	{
		// Warning
		Result = EDataValidationResult::Invalid;
		ValidationErrors.AddError(FText::Format(LOCTEXT("NoInput", "Condition does not have an assigned Input Action reference."),
			FText::AsCultureInvariant(GetNameSafe(this))));
	}

	return Result;
}
#endif
// End UObjectInterface
#undef LOCTEXT_NAMESPACE