// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet_Dummy.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class SAMBA_API UAttributeSet_Dummy : public UAttributeSet
{
	GENERATED_BODY()

	UAttributeSet_Dummy(const FObjectInitializer& ObjectInitializer);
public:
	// Dummy Value.
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Dummy", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Sclera;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Dummy, Sclera)

	// Other Dummy value
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Dummy", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Pulchritude;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Dummy, Pulchritude)

};
