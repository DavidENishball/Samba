// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/TargetType/TargetType_SimpleFilter.h"
//#include <GameplayAbilityTypes.h>

void UTargetType_SimpleFilter::GetTargets_Implementation(UAbilitySystemComponent* Instigator, AActor* EffectCauser, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	if (!bAllowDeadTargets)
	{
		if (USambaGameplayStatics::IsActorDead(EventData.Target))
		{
			// Target is dead.
			return;
		}
	}

	if (bIgnoreInstigator)
	{
		if (EventData.Target == EventData.Instigator)
		{
			return;
		}
	}

	ETeamAttitude::Type Attitude = USambaGameplayStatics::GetAttitude(Instigator->GetAvatarActor(), EventData.Target);

	if (TargetAttitudes.Contains(Attitude) == false)
	{
		return;
	}
	AActor* MutableActor = const_cast<AActor*>(EventData.Target.Get());
	OutActors.Add(MutableActor);

}
