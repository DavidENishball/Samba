// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/TargetType/TargetType.h"
#include "Abilities/GameplayAbilityTypes.h"


void UTargetType::GetTargets_Implementation(UAbilitySystemComponent* Instigator, AActor* EffectCauser, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	// Override me.
	ensureAlways(false);
}
