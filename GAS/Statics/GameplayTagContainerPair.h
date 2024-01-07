// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "GameplayTagContainerPair.generated.h"

// A data holder for pairing two montages together.
USTRUCT(BlueprintType)
struct FGameplayTagContainerPair
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer First;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer Second;
};