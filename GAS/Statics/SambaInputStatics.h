// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include <GenericTeamAgentInterface.h>
#include "SambaInputStatics.generated.h"
// Statics related to gameplay and AI.  Stuff like if abilities can be used, or death.

UCLASS()
class SAMBA_API USambaInputStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static FVector GetBoundAxisValue(const UEnhancedInputComponent* EnhancedInputComp, const UInputAction* Action);
};