// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Animation/AnimMontageSelector.h"
#include "AnimMontageSelector_Single.generated.h"

/**
 * A single montage, the same every time.
 */
UCLASS()
class SAMBA_API UAnimMontageSelector_Single : public UAnimMontageSelector
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* Montage;

	virtual UAnimMontage* SelectMontageByEventContext_Implementation(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEffectContextHandle& Context) override;
};
