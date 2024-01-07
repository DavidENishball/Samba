// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GenericTeamAgentInterface.h>
#include "TargetType.generated.h"

class UAbilitySystemComponent;
struct FGameplayEventData;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract, EditInlineNew, meta = (ShowWorldContextPin))
class SAMBA_API UTargetType : public UObject
{
	GENERATED_BODY()

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewTargetDataDelegate, UTargetType*, Source, TArray<TargetData, const FGameplayAbilityTargetDataHandle&, Data);

public:
	// Constructor and overrides
	UTargetType()
	{
		bIgnoreInstigator = true;
		TargetAttitudes.Add(ETeamAttitude::Hostile);
		TargetAttitudes.Add(ETeamAttitude::Neutral);
	}

	// The source of this target type.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	UObject* Source;

	// Allow targeting creatures with these attitudes, relative to owner.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Targeting")
	TSet<TEnumAsByte<ETeamAttitude::Type>> TargetAttitudes;

	// TODO: Ignore dead or allow?
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Targeting")
	bool bAllowDeadTargets;

	// If true, ignore the owning actor of this targettype
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Targeting")
	bool bIgnoreInstigator;

	/** Called to determine targets to apply gameplay effects to.  Instigator is the source, Causer is the weapon or projectile. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targeting")
	void GetTargets(UAbilitySystemComponent* Instigator, AActor* EffectCauser, FGameplayEventData EventData,
		TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
	virtual void GetTargets_Implementation(UAbilitySystemComponent* Instigator, AActor* EffectCauser, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;

	protected:
};
