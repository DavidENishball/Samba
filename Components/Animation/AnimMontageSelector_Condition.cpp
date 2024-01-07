// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Animation/AnimMontageSelector_Condition.h"
#include <GameplayAbilitySpecHandle.h>
#include "../../GAS/AbilityConditions/AbilityConditionFunctor.h"
#include <Abilities/GameplayAbility.h>
#include <AbilitySystemGlobals.h>
#include <AbilitySystemComponent.h>

UAnimMontage* UAnimMontageSelector_Condition::SelectMontageByEventContext_Implementation(const class USkeletalMeshComponent* SkeletalMesh, const FGameplayTag& Tag, const FGameplayEffectContextHandle& Context)
{
	bool bPass = true;

	for (const UAbilityConditionFunctor* IteratedFunctor : Conditions)
	{
		if (IteratedFunctor == nullptr)
		{
			continue;
		}
		const UGameplayAbility* ContextAbility = Context.GetAbility();
		FGameplayAbilitySpecHandle Handle;
		Handle = ContextAbility ? ContextAbility->GetCurrentAbilitySpecHandle() : FGameplayAbilitySpecHandle();


		// Populate avatar info.
		FGameplayAbilityActorInfo NewInfo = FGameplayAbilityActorInfo();
		NewInfo.SkeletalMeshComponent = const_cast<USkeletalMeshComponent*>(SkeletalMesh);
		NewInfo.AvatarActor = SkeletalMesh->GetOwner();
		NewInfo.AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(SkeletalMesh->GetOwner());
		NewInfo.SkeletalMeshComponent->GetAnimInstance();
		if (NewInfo.AbilitySystemComponent != nullptr)
		{
			NewInfo.OwnerActor = NewInfo.AbilitySystemComponent->GetOwnerActor();
		}
		else
		{
			NewInfo.OwnerActor = SkeletalMesh->GetOwner();
		}

		// TODO: Make an Event Data version of this that can get more context?  Ability Conditions don't use context, annoyingly.

		if (IteratedFunctor->EvaluateCondition(Handle, &NewInfo, nullptr, nullptr, nullptr) == false)
		{
			bPass = false;
			break;
		}
	}

	if (bPass)
	{
		if (PassMontage != nullptr)
		{
			return PassMontage->SelectMontageByEventContext(SkeletalMesh, Tag, Context);
		}
		else
		{
			return nullptr;
		}

	}
	else
	{
		if (FailMontage != nullptr)
		{
			return FailMontage->SelectMontageByEventContext(SkeletalMesh, Tag, Context);
		}
		else
		{
			return nullptr;
		}
	}
}
