// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "SambaMontageStatics.generated.h"
// Statics relevant to Montages.

// TODO: Put some statics here.


UCLASS()
class SAMBA_API USambaMontageStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable)
	static float GetDurationForMontageSection(UAnimMontage* Montage, const FName SectionName /*= NAME_None*/);
};