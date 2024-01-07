// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Animation/AnimMontageSelector.h"
#include "AnimMontageSelector_Condition.generated.h"

class UAbilityConditionFunctor;
/**
 * Choose a montage based on if the owner passes a collection of ability conditions.
 */
UCLASS()
class SAMBA_API UAnimMontageSelector_Condition : public UAnimMontageSelector
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
	TArray<UAbilityConditionFunctor*> Conditions;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontageSelector* PassMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontageSelector* FailMontage;

	virtual UAnimMontage* SelectMontageByEventContext_Implementation(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEffectContextHandle& Context) override;
};
