// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Framework/SambaGameplayAbility.h"
#include "Abilities/GameplayAbilityTypes.h"


void USambaGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}