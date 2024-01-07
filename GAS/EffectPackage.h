// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <GameplayEffect.h>
#include "EffectPackage.generated.h"

class UTargetType;

/**
 * Effect packages combine a Targeting Method and Gameplay Effects.
 */
USTRUCT(BlueprintType)
struct FEffectPackage
{
	GENERATED_BODY()

public:

	// A label for this package.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Tag;

	// The effects to apply.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayEffect>> Effects;

	// All initial targets will be compared to this TargetType for filtering, etc. There's a possibility of this creating more targets.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UTargetType* TargetTypeData;
};
