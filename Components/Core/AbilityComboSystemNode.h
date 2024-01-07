// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Interfaces/InputBindingsInterface.h"
#include "AbilityComboSystemNode.generated.h"

class UGameplayAbility;
class UAbilityConditionFunctor;

// A link in the combo system.
USTRUCT(BlueprintType)
struct FAbilityComboSystemLink
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
	TArray<UAbilityConditionFunctor*> Conditions;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UGameplayAbility> LinkedAbility;

};

/**
 * A data-only class that represents a node in the combo graph.  It is associated with a particular Ability.
 */
UCLASS(BlueprintType, Blueprintable)
class SAMBA_API UAbilityComboSystemNode : public UObject, public IInputBindingsInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FAbilityComboSystemLink> Links;


	FAbilityComboSystemLink GetBestLink (const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const;

	// Begin IInputBindingsInterface
	virtual TSet<UInputAction*> GetInputActions_Implementation() const override;
	// End IInputBindingsInterface
};
