// Fill out your copyright notice in the Description page of Project Settings.


#include "SambaGameplayStatics.h"
#include <NativeGameplayTags.h>
#include <AbilitySystemComponent.h>
#include <AttributeSet.h>
#include "Components/Core/TeamComponent.h"
#include "../TagDefinitions/SambaGameplayTags.h"
#include <AbilitySystemGlobals.h>


UAttributeSet* USambaGameplayStatics::FindOrGrantAttributeSet(UAbilitySystemComponent* ASC, TSubclassOf<class UAttributeSet> NewSet)
{
	if (ASC == nullptr)
	{
		return nullptr;
	}

	for (UAttributeSet* Set : ASC->GetSpawnedAttributes())
	{
		if (Set && Set->IsA(NewSet))
		{
			return Set;
		}
	}

	// Grant set instead.
	UAttributeSet* SpawnedSet = NewObject<UAttributeSet>(ASC->GetOwner(), NewSet);
	ASC->AddAttributeSetSubobject(SpawnedSet);
	return SpawnedSet;
}


FGameplayAbilitySpecHandle USambaGameplayStatics::GetAbilitySpecHandleByClass(const UAbilitySystemComponent* ASC, const TSubclassOf<class UGameplayAbility> AbilityClass)
{
	if (!ensureAlways(ASC))
	{
		return FGameplayAbilitySpecHandle();
	}
	if (!ensureAlways(AbilityClass != nullptr))
	{
		return FGameplayAbilitySpecHandle();
	}

	const UGameplayAbility* const InAbilityCDO = AbilityClass.GetDefaultObject();

	for (const FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if (Spec.Ability == InAbilityCDO)
		{
			return Spec.Handle;
		}
	}
	return FGameplayAbilitySpecHandle();
}

FGameplayAbilitySpecHandle USambaGameplayStatics::FindOrGrantAbilitySpecHandleByClass(UAbilitySystemComponent* ASC, const TSubclassOf<class UGameplayAbility> AbilityClass)
{
	FGameplayAbilitySpecHandle FoundHandle = GetAbilitySpecHandleByClass(ASC, AbilityClass);
	if (FoundHandle.IsValid())
	{
		return FoundHandle;
	}

	FoundHandle = ASC->K2_GiveAbility(AbilityClass,0,0);

	return FoundHandle;
}

const UObject* USambaGameplayStatics::ChooseObjectFromEventData(const FGameplayEventData& EventData, EEventDataVariableFilter Enum)
{
	switch (Enum)
	{
	case EEventDataVariableFilter::Instigator:
		return EventData.Instigator;
		break;
	case EEventDataVariableFilter::OptionalObject:
		return EventData.OptionalObject;
		break;
	case EEventDataVariableFilter::OptionalObject2:
		return EventData.OptionalObject2;
		break;
	case EEventDataVariableFilter::Target:
		return EventData.Target;
		break;

	default:
		ensureMsgf(false, TEXT("USambaGameplayStatics::ChooseObjectFromEventData - Invalid enum for choose object"));
	}

	return nullptr;
}

ETeamAttitude::Type USambaGameplayStatics::GetAttitude(const AActor* Origin, const AActor* Target)
{
	UTeamComponent* TeamComponent = Origin->FindComponentByClass<UTeamComponent>();
	if (TeamComponent)
	{
		return TeamComponent->GetAttitude(Target);
	}

	return ETeamAttitude::Neutral;
}

bool USambaGameplayStatics::IsActorDead(const AActor* Actor)
{
	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor);
	if (ASC == nullptr)
	{
		return false;
	}

	return ASC->HasMatchingGameplayTag(TAG_Character_State_Dead);
}

bool USambaGameplayStatics::IsGameplayAbilitySpecHandleValid(const FGameplayAbilitySpecHandle& Handle)
{
	return Handle.IsValid();
}
