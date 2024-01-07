// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include <GenericTeamAgentInterface.h>
#include "SambaGameplayStatics.generated.h"
// Statics related to gameplay and AI.  Stuff like if abilities can be used, or death.


// What part of EventData to access.
UENUM(BlueprintType)
enum class EEventDataVariableFilter : uint8
{
	Instigator,
	Target,
	OptionalObject,
	OptionalObject2,
	TargetData,
	TargetingActor,
};

UCLASS()
class SAMBA_API USambaGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static UAttributeSet* FindOrGrantAttributeSet(UAbilitySystemComponent* ASC, TSubclassOf<class UAttributeSet> NewSet);

	UFUNCTION(BlueprintCallable)
	static FGameplayAbilitySpecHandle GetAbilitySpecHandleByClass(const UAbilitySystemComponent* ASC, const TSubclassOf<class UGameplayAbility> InAbilityToActivate);

	UFUNCTION(BlueprintCallable)
	static FGameplayAbilitySpecHandle FindOrGrantAbilitySpecHandleByClass(UAbilitySystemComponent* ASC, const TSubclassOf<class UGameplayAbility> AbilityClass);

	UFUNCTION(BlueprintCallable)
	static const UObject* ChooseObjectFromEventData(const FGameplayEventData& EventData, EEventDataVariableFilter Enum);

	UFUNCTION(BlueprintCallable)
	static ETeamAttitude::Type GetAttitude(const AActor* Origin, const AActor* Target);

	UFUNCTION(BlueprintCallable)
	static bool IsActorDead(const AActor* Target);

	UFUNCTION(BlueprintCallable)
	bool IsGameplayAbilitySpecHandleValid(const FGameplayAbilitySpecHandle& Handle);
};