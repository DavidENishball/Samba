// Fill out your copyright notice in the Description page of Project Settings.


#include "SambaInputStatics.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"



FVector USambaInputStatics::GetBoundAxisValue(const UEnhancedInputComponent* EnhancedInputComp, const UInputAction* Action)
{
	FInputActionValue BoundValue = EnhancedInputComp->GetBoundActionValue(Action);
	return BoundValue.Get<FVector>();
}
