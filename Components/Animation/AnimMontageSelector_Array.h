// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Animation/AnimMontageSelector.h"
#include "AnimMontageSelector_Array.generated.h"

/**
 * Check sub conditions until you find a valid montage.  Used for conditional behaviors.
 */
UCLASS()
class SAMBA_API UAnimMontageSelector_Array : public UAnimMontageSelector
{
	GENERATED_BODY()
	
public:

	// Test each selector in this array in order, using the first valid montage returned.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
	TArray<UAnimMontageSelector*> Array;

	// If all selectors in the array fail, use this one.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
	UAnimMontage* FallbackMontage;


	virtual UAnimMontage* SelectMontageByEventContext_Implementation(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEffectContextHandle& Context) override;
};
