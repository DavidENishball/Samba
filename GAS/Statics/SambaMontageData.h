// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "SambaMontageData.generated.h"
class UAnimMontage;

// A data holder for playing a montage, literal or by tag, along with starting section and play rate.

USTRUCT(BlueprintType)
struct FSambaMontageData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* SpecificMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag MontageTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StartTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName StartSection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PlayRate = 1;

	UAnimMontage* ChooseMontage(const class AActor* Actor);
};