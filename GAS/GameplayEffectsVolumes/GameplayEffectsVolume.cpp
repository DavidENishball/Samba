// Copyright Big Time Studios Ltd. All Rights Reserved.


#include "GameplayEffectsVolume.h"
#include "Components/PrimitiveComponent.h"
#include "AbilitySystemComponent.h"
#include "Engine/EngineTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Algo/Transform.h"
#include <GameplayCueFunctionLibrary.h>
#include <GameplayEffectTypes.h>
#include <AbilitySystemGlobals.h>
#include "../TagDefinitions/SambaGameplayTags.h"
#include "../TargetType/TargetType.h"
#include "../Statics/SambaGameplayStatics.h"

// Sets default values
AGameplayEffectsVolume::AGameplayEffectsVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	bApplyEnterEffectsOnTargetsWithinVolumeOnSpawn = true;
	bIgnoreDeadTargets = true;
	bIgnoreAvatar = true;
	AttitudesToTarget.Add(ETeamAttitude::Hostile);
	AttitudesToTarget.Add(ETeamAttitude::Neutral);
	bTargetsEnterOnlyOnce = true;
	bRemoveEnterEffectsOnExit = false;
}

AActor* AGameplayEffectsVolume::GetAvatarActor() const
{
	if (OwnerComponent)
	{
		return OwnerComponent->GetAvatarActor();
	}
	return nullptr;
}

void AGameplayEffectsVolume::Activate()
{
	bIsActive = true;

	if (GameplayEffectsAppliedOnEnter.Num() == 0)
	{
		GameplayEffectsAppliedOnEnter = DefaultGameplayEffectsAppliedOnEnter;
	}

	if (EffectPackagesAppliedOnEnter.Num() == 0)
	{
		EffectPackagesAppliedOnEnter = DefaultEffectPackagesAppliedOnEnter;
	}

	// Bind begin overlap reaction to all designated volume components.
	for (UPrimitiveComponent* IteratedPrimitive : VolumeComponents)
	{
		IteratedPrimitive->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGameplayEffectsVolume::HandleAnyPrimitiveEntered);

		IteratedPrimitive->OnComponentEndOverlap.AddUniqueDynamic(this, &AGameplayEffectsVolume::HandleAnyPrimitiveExited);
	}

	// Iterate again now that all bindings are done.
	for (UPrimitiveComponent* IteratedPrimitive : VolumeComponents)
	{
		IteratedPrimitive->SetGenerateOverlapEvents(true);
	}

	// Do it again to catch anyone already inside.
	for (UPrimitiveComponent* IteratedPrimitive : VolumeComponents)
	{
		for (const FOverlapInfo& IteratedInfo : IteratedPrimitive->GetOverlapInfos())
		{
			const FHitResult& HitResult = IteratedInfo.OverlapInfo;
			HandleAnyPrimitiveEntered(IteratedPrimitive, HitResult.GetActor(), HitResult.GetComponent(), HitResult.ElementIndex, IteratedInfo.bFromSweep, HitResult);
		}
	}


	// Queue first frame behavior.
	//FTimerHandle UnusedHandle = GetWorldTimerManager().SetTimerForNextTick(this, &AGameplayEffectsVolume::FirstFrameBehavior);
	bIsActive = true;
}

void AGameplayEffectsVolume::SetDebugDraw(bool bOn)
{
	this->SetActorHiddenInGame(!bOn);

	for (UPrimitiveComponent* IteratedPrimitive : VolumeComponents)
	{
		IteratedPrimitive->SetHiddenInGame(!bOn);
	}
}

void AGameplayEffectsVolume::SetDuration(float Duration)
{
	FTimerHandle TempHandle;
	GetWorldTimerManager().SetTimer(TempHandle, this, &AGameplayEffectsVolume::DurationExpired, Duration, false);
}

void AGameplayEffectsVolume::SetVolumeSize_Implementation(FVector NewSize)
{
	// Override me!
}

void AGameplayEffectsVolume::DurationExpired()
{
	if (OwnerComponent == nullptr)
	{
		return;
	}
	FGameplayCueParameters TempParams;
	TempParams.Instigator = GetInstigator();
	TempParams.SourceObject = this;
	TempParams.TargetAttachComponent = RootComponent;

	if (OwnerComponent)
	{
		QuickInstantCue(CueOnExpire);
	}

	this->Destroy();
}

TSet<AActor*> AGameplayEffectsVolume::GetAllActorsWithinVolumes() const
{
	TSet<AActor*> OutputSet;

	for (const UPrimitiveComponent* IteratedPrimitive : VolumeComponents)
	{
		if (IteratedPrimitive != nullptr)
		{
			TSet<AActor*> NewSet;
			IteratedPrimitive->GetOverlappingActors(NewSet);
			OutputSet.Append(NewSet);
		}
	}

	return OutputSet;
}

bool AGameplayEffectsVolume::IsActorWithinAnyVolume(const AActor* ArgActor) const
{
	if (ArgActor == nullptr)
	{
		return false;
	}

	for (const UPrimitiveComponent* IteratedPrimitive : VolumeComponents)
	{
		if (IteratedPrimitive != nullptr)
		{
			if (IteratedPrimitive->IsOverlappingActor(ArgActor))
			{
				return true;
			}
		}
	}

	return false;
}

TArray<UPrimitiveComponent*> AGameplayEffectsVolume::GetVolumesIntersectingActor(const AActor* ArgActor) const
{
	TArray<UPrimitiveComponent*> OutputArray;

	for (UPrimitiveComponent* IteratedPrimitive : VolumeComponents)
	{
		if (IteratedPrimitive != nullptr)
		{
			if (IteratedPrimitive->IsOverlappingActor(ArgActor))
			{
				OutputArray.Add(IteratedPrimitive);
			}
		}
	}

	return OutputArray;
}

void AGameplayEffectsVolume::QuickInstantCue(FGameplayTag CueTag)
{
	if (CueTag.IsValid() == false)
	{
		return;
	}

	FGameplayCueParameters CueParam;

	CueParam.Location = GetActorLocation();
	CueParam.Normal = GetActorForwardVector();
	CueParam.Instigator = this;
	CueParam.EffectCauser = this;
	CueParam.SourceObject = this;
	CueParam.TargetAttachComponent = this->RootComponent;

	// Interface IAbilitySystemInterface ensures it finds the Owner component.
	UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, CueTag, CueParam);
}

void AGameplayEffectsVolume::HandleAnyPrimitiveEntered_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIgnoreAvatar)
	{
		if (OtherActor == GetAvatarActor())
		{
			return;
		}
	}
	UAbilitySystemComponent* OtherActorASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (OtherActorASC == nullptr)
	{
		// No ASC.  We don't care.
		return;
	}

	if (OtherActorASC->HasMatchingGameplayTag(TAG_Character_State_IgnoreSweeps))
	{
		// Actor is set to Ignore Sweeps.  Don't do anything.
		// TODO: What if they lose the tag while inside?
		return;
	}

	// Apply the Enter effects.

	// Prevent double activation by only applying effects for the first volume being overlapped
	TArray<UPrimitiveComponent*> VolumesIntersectingActor = GetVolumesIntersectingActor(OtherActor);
	if (VolumesIntersectingActor.Num() == 1 && VolumesIntersectingActor[0] == OverlappedComponent)
	{
		TArray<FActiveGameplayEffectHandle> AppliedEffectHandles = TryApplyEnterEffects(OverlappedComponent,OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

		for (const FActiveGameplayEffectHandle& IteratedHandle : AppliedEffectHandles)
		{
			ActorToCachedEnterEffectsMap.Add(OtherActor, IteratedHandle);
		}

		if (AppliedEffectHandles.Num() > 0)
		{
			// Get more specific location info.
			//OwnerComponent->ExecuteGameplayCue(FGameplayTag::RequestGameplayTag(TEXT("GameplayCue.Burst.Hit"), false), ;
		}
	}
}

void AGameplayEffectsVolume::HandleAnyPrimitiveExited_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// We only care about actors with ability components.
	UAbilitySystemComponent* FoundASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);

	if (FoundASC == nullptr)
	{
		return;
	}

	// Prevent early removal by only applying effects if all volumes are exited.
	TArray<UPrimitiveComponent*> VolumesIntersectingActor = GetVolumesIntersectingActor(OtherActor);
	if (VolumesIntersectingActor.Num() != 0)
	{
		return;
	}

	if (bRemoveEnterEffectsOnExit)
	{
		TArray<FActiveGameplayEffectHandle> AppliedEffectHandles;
		ActorToCachedEnterEffectsMap.MultiFind(OtherActor, AppliedEffectHandles);

		for (const FActiveGameplayEffectHandle& IteratedHandle : AppliedEffectHandles)
		{
			FoundASC->RemoveActiveGameplayEffect(IteratedHandle);
		}

		ActorToCachedEnterEffectsMap.Remove(OtherActor);
	}
}

void AGameplayEffectsVolume::RemoveAllActiveEffectsWhenVolumeIsDestroyed()
{
	if (bRemoveEnterEffectsOnExit)
	{
		TArray<AActor*> AllActors;
		ActorToCachedEnterEffectsMap.GetKeys(AllActors);
		for (AActor* Key : AllActors)
		{
			UAbilitySystemComponent* FoundASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Key);

			// We should only track actors with ASC.
			if (!ensureAlways(FoundASC))
			{
				continue;
			}

			TArray<FActiveGameplayEffectHandle> AppliedEffectHandles;
			ActorToCachedEnterEffectsMap.MultiFind(Key, AppliedEffectHandles);

			for (const FActiveGameplayEffectHandle& IteratedHandle : AppliedEffectHandles)
			{
				FoundASC->RemoveActiveGameplayEffect(IteratedHandle);
			}
		}
		ActorToCachedEnterEffectsMap.Empty();
	}
}

void AGameplayEffectsVolume::Destroyed()
{
	RemoveAllActiveEffectsWhenVolumeIsDestroyed();

	Super::Destroyed();
}

TArray<FActiveGameplayEffectHandle> AGameplayEffectsVolume::TryApplyEnterEffects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<FActiveGameplayEffectHandle> OutputArray;

	if (GameplayEffectsAppliedOnEnter.Num() == 0 && EffectPackagesAppliedOnEnter.Num() == 0)
	{
		return OutputArray;
	}

	if (MaximumActivationsForEnter > 0 && TotalEnterActivations >= MaximumActivationsForEnter)
	{
		return OutputArray;
	}

	TArray<AActor*> TempArray;

	TempArray.Add(OtherActor);

	// Filter.
	TempArray = FilterEnterTargets(TempArray);

	if (TempArray.Num() == 0)
	{
		// No targets, end early.
		return OutputArray;
	}

	// Apply all specs. 
	// This assumes the specs themselves handle the target filtering.

	// Checked in the Filter step.
	UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OtherActor);


	FGameplayEventData EventData;
	//EventData.ContextHandle = EffectContext;
	EventData.Instigator = OwnerComponent->GetOwner();
	EventData.Target = OtherActor;

	for (FEffectPackage& IteratedPackage : EffectPackagesAppliedOnEnter)
	{
		TArray<FHitResult> CapturedHitResults;
		TArray<AActor*> CapturedActorResults;
		TArray<AActor*> InitialTargets({ OtherActor });
		IteratedPackage.TargetTypeData->GetTargets(this->OwnerComponent, GetAvatarActor(), EventData, CapturedHitResults, CapturedActorResults);

		// There's a chance TargetType generates more targets, or reverses them.
		for (AActor* IteratedActor : CapturedActorResults)
		{
			UAbilitySystemComponent* IteratedASC = IteratedActor->FindComponentByClass<UAbilitySystemComponent>();
			if (IteratedASC != nullptr)
			{
				for (TSubclassOf<UGameplayEffect> IteratedEffect : IteratedPackage.Effects)
				{
					FGameplayEffectContextHandle EffectContext = OwnerComponent->MakeEffectContext();
					EffectContext.AddSourceObject(this);
					EffectContext.AddActors({ this, IteratedActor });
					EffectContext.AddInstigator(GetAvatarActor(), this);
					EffectContext.SetAbility(OwnerAbility);
					OutputArray.Add(OwnerComponent->BP_ApplyGameplayEffectToTarget(IteratedEffect, TargetASC, 0, EffectContext));
				}
			}
		}
	}

	for (TSubclassOf<UGameplayEffect> IteratedEffect : GameplayEffectsAppliedOnEnter)
	{
		FGameplayEffectContextHandle EffectContext = OwnerComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		EffectContext.AddActors({ this, OtherActor });
		EffectContext.AddInstigator(GetAvatarActor(), this);
		EffectContext.SetAbility(OwnerAbility);
		OutputArray.Add(OwnerComponent->BP_ApplyGameplayEffectToTarget(IteratedEffect, TargetASC, 0, EffectContext));
	}

	// Did we apply any effects?
	if (OutputArray.Num() > 0)
	{
		TotalEnterActivations++;

		if (MaximumActivationsForEnter > 0 && TotalEnterActivations >= MaximumActivationsForEnter && bDestroyAfterMaximumActivations)
		{
			QuickInstantCue(CueOnMaximumActivation);
			Destroy();
		}
		else
		{
			QuickInstantCue(CueOnActivation);

			FHitResult SweepHit;

			OtherComp->SweepComponent(SweepHit, FVector::ZeroVector, OverlappedComponent->GetComponentLocation(), OverlappedComponent->GetComponentRotation().Quaternion(), OverlappedComponent->GetCollisionShape());

			//DrawDebugCrosshairs(this->GetWorld(), SweepHit.ImpactPoint, FRotator(), 20.0f, FColor::White, true, 2.0f); 
			// TODO: Play a cue at the overlap point.
			/*FHitResult SweepHit;
			OverlappedComponent->SweepComponent(SweepHit, OverlappedComponent->GetComponentLocation(), OverlappedComponent->GetComponentLocation(), OverlappedComponent->GetComponentRotation().Quaternion(), OverlappedComponent->GetCollisionShape());
			DrawDebugCrosshairs(this->GetWorld(), SweepHit.ImpactPoint, FRotator(), 20.0f, FColor::White, true, 2.0f);*/

		}
		OnAnyEnterEffectsApplied.Broadcast(this, OutputArray);  // I'm trusting that whoever is consuming this can use the handles to find precisely who was expected.  
		// TODO: Maybe make a static function to do that?
	}
	// Location cue.
	if (OutputArray.Num() > 0)
	{
		
	}
	return OutputArray;
}



TArray<AActor*> AGameplayEffectsVolume::FilterEnterTargets(TArray<AActor*> PossibleTargets) const
{
	TArray<AActor*> ValidTargets;

	if (OwnerComponent != nullptr)
	{
		TSet<AActor*> AlreadyAffectedActors;
		ActorToCachedEnterEffectsMap.GetKeys(AlreadyAffectedActors);

		for (AActor* IteratedActor : PossibleTargets)
		{
			if (IteratedActor == nullptr)
			{
				continue;
			}

			if (bTargetsEnterOnlyOnce && AlreadyAffectedActors.Contains(IteratedActor))
			{
				// Target was affected by this volume already.
				continue;
			}

			UAbilitySystemComponent* IteratedASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(IteratedActor);
			if (IteratedASC == nullptr)
			{
				// No ASC.  Skip it!
				continue;
			}

			// Todo: prevent multiple entry.
			if (false)
			{
				if (AlreadyAffectedActors.Contains(IteratedActor))
				{
					continue;
				}
			}

			ETeamAttitude::Type Attitude = USambaGameplayStatics::GetAttitude(GetAvatarActor(), IteratedActor);
			if (AttitudesToTarget.Contains(Attitude))
			{
				ValidTargets.Add(IteratedActor);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AGameplayEffectsVolume::FilterEnterTargets: had a null OwnerComponent [%s]"), *GetName());
	}



	return ValidTargets;
}

// Called when the game starts or when spawned
void AGameplayEffectsVolume::BeginPlay()
{
	Super::BeginPlay();

	if (!bActivateManually)
	{
		Activate();
	}



}
