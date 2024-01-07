// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AnimMontageSelector.generated.h"

class UAnimMontage;

/**
 * A functor object that chooses a anim montage based on context or other logic.
 */
UCLASS(BlueprintType, Blueprintable, Abstract, editinlinenew, DefaultToInstanced)
class SAMBA_API UAnimMontageSelector : public UObject
{
	GENERATED_BODY()
	public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UAnimMontage* SelectMontageByEventData(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEventData& Data );
		virtual UAnimMontage* SelectMontageByEventData_Implementation(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEventData& Data);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UAnimMontage* SelectMontageByEventContext(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEffectContextHandle& Context);
	virtual UAnimMontage* SelectMontageByEventContext_Implementation(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEffectContextHandle& Context);
};
