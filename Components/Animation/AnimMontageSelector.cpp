// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Animation/AnimMontageSelector.h"

UAnimMontage* UAnimMontageSelector::SelectMontageByEventData_Implementation(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEventData& Data)
{
	return SelectMontageByEventContext(SkeletalMesh, Tag, Data.ContextHandle);
}

UAnimMontage* UAnimMontageSelector::SelectMontageByEventContext_Implementation(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEffectContextHandle& Context)
{
	// Override me!
	ensureAlways(false);
	return nullptr;
}

