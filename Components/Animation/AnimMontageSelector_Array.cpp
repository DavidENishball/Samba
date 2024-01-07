// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Animation/AnimMontageSelector_Array.h"

UAnimMontage* UAnimMontageSelector_Array::SelectMontageByEventContext_Implementation(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEffectContextHandle& Context)
{
	for (UAnimMontageSelector* IteratedSubSelector : Array)
	{
		if (IteratedSubSelector == nullptr)
		{
			continue;
		}
		UAnimMontage* ChosenMontage = IteratedSubSelector->SelectMontageByEventContext(SkeletalMesh, Tag, Context);
		if (ChosenMontage != nullptr)
		{
			return ChosenMontage;
		}
	}

	// Sub Selectors all failed.
	return FallbackMontage;
}
