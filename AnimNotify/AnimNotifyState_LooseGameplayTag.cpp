// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_LooseGameplayTag.h"
#include <AbilitySystemComponent.h>

void UAnimNotifyState_LooseGameplayTag::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{

		UAbilitySystemComponent* ASC = MeshComp->GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
		if (ASC == nullptr)
		{
			return;
		}
		ASC->AddLooseGameplayTags(Tags);
	}
}

void UAnimNotifyState_LooseGameplayTag::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		UAbilitySystemComponent* ASC = MeshComp->GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
		if (ASC == nullptr)
		{
			return;
		}
		ASC->RemoveLooseGameplayTags(Tags);
	}
}
