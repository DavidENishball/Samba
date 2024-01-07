// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/TargetType/TargetType.h"
#include "TargetType_SimpleFilter.generated.h"

/**
 * Filters relevant targets by attitude, and if dead.
 */
UCLASS()
class SAMBA_API UTargetType_SimpleFilter : public UTargetType
{
	GENERATED_BODY()
	
	public:

	void GetTargets_Implementation(UAbilitySystemComponent* Instigator, AActor* EffectCauser, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor *>& OutActors) const override;
};
