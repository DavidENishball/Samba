// Fill out your copyright notice in the Description page of Project Settings.

#define LOCTEXT_NAMESPACE "USambaAbility_Montage"
#include "GAS/Abilities/Framework/SambaAbility_Montage.h"
#include <Abilities/Tasks/AbilityTask_PlayMontageAndWait.h>
#include <Abilities/Tasks/AbilityTask_WaitGameplayEvent.h>
#include <Abilities/GameplayAbilityTypes.h>
#include "AbilitySystemComponent.h"

void USambaAbility_Montage::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (TriggerEventData != nullptr && TriggerEventData->Target != nullptr)
	{
		// Store trigger target.
	}

	UAnimMontage* ChosenMontage = MontageData.SpecificMontage; // nullpMontageData.ChooseMontage(ActorInfo->AvatarActor);

	UAbilityTask_PlayMontageAndWait* NewMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName("MontageTask"), ChosenMontage, MontageData.PlayRate, MontageData.StartSection); // Todo: make a static for this.

	NewMontageTask->OnBlendOut.AddDynamic(this, &USambaAbility_Montage::HandleMontageCompleted);
	NewMontageTask->OnCompleted.AddDynamic(this, &USambaAbility_Montage::HandleMontageCompleted);
	NewMontageTask->OnInterrupted.AddDynamic(this, &USambaAbility_Montage::HandleMontageInterrupted);
	NewMontageTask->OnCancelled.AddDynamic(this, &USambaAbility_Montage::HandleMontageCancelled);

	// Assume that a different system will respond to notifies.

	NewMontageTask->ReadyForActivation();
}


bool USambaAbility_Montage::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}

	for (const FGameplayTagContainerPair& IteratedPair : ActivationBlockExceptions)
	{
		// Check blocking.
		if (ActorInfo->AbilitySystemComponent->HasAnyMatchingGameplayTags(IteratedPair.First))
		{
			// Check exceptions.
			if (ActorInfo->AbilitySystemComponent->HasAnyMatchingGameplayTags(IteratedPair.Second) == false) 
			{
				return false;
			}
		}
	}

	return true;
}

void USambaAbility_Montage::HandleMontageCompleted()
{
	// All done.
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, true);
}

void USambaAbility_Montage::HandleMontageInterrupted()
{
	// Interrupt early, so end.
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, true);
}

void USambaAbility_Montage::HandleMontageCancelled()
{
	// Montage stopped, so stop.
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, true);
}


// Begin UObject Interface
#if WITH_EDITOR
#include <../../../../../../../Source/Runtime/CoreUObject/Public/Misc/DataValidation.h>
EDataValidationResult USambaAbility_Montage::IsDataValid(FDataValidationContext& ValidationErrors) const
{
	EDataValidationResult Result = Super::IsDataValid(ValidationErrors);

	if (MontageData.MontageTag.IsValid() == false && MontageData.SpecificMontage == nullptr)
	{
		// Warning
		Result = EDataValidationResult::Invalid;
		ValidationErrors.AddError(FText::Format(LOCTEXT("MontageAbility_RedundantMontage", "Ability {0}: Montage data does not have montage pointer or montage tag specified."),
			FText::AsCultureInvariant(GetNameSafe(this))));
	}

	return Result;
}
#endif
// End UObjectInterface

#undef LOCTEXT_NAMESPACE