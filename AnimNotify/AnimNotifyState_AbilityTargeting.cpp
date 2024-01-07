// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_AbilityTargeting.h"
#include <AbilitySystemComponent.h>

void UAnimNotifyState_AbilityTargeting::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{

		UAbilitySystemComponent* ASC = MeshComp->GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
		if (ASC == nullptr)
		{
			return;
		}

		UGameplayAbility* AnimatingAbilityInstance = ASC->GetAnimatingAbility();

		if (AnimatingAbilityInstance)
		{
			UE_LOG(LogTemp, Log, TEXT("Current animating ability is: %s"), *AnimatingAbilityInstance->GetName())
		}

	}
}

void UAnimNotifyState_AbilityTargeting::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		UAbilitySystemComponent* ASC = MeshComp->GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
		if (ASC == nullptr)
		{
			return;
		}
		// TODO: Do something here.
	}
}
