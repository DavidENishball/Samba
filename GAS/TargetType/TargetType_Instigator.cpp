// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/TargetType/TargetType_Instigator.h"

void UTargetType_Instigator::GetTargets_Implementation(UAbilitySystemComponent* Instigator, AActor* EffectCauser, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	OutActors.Add(Instigator->GetOwner());
}