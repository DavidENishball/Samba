// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Animation/AnimMontageSelector_Single.h"

UAnimMontage* UAnimMontageSelector_Single::SelectMontageByEventContext_Implementation(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEffectContextHandle& Context)
{
	return Montage;
}
