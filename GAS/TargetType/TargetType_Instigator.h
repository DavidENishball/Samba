// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/TargetType/TargetType.h"
#include "TargetType_Instigator.generated.h"

/**
 * Target type that targets the instigator of the ability.
 */
UCLASS()
class SAMBA_API UTargetType_Instigator : public UTargetType
{
	GENERATED_BODY()
public:
	virtual void GetTargets_Implementation(UAbilitySystemComponent* Instigator, AActor* EffectCauser, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};
