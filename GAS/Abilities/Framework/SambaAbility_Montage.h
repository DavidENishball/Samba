// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/Framework/SambaGameplayAbility.h"
#include "../../Statics/SambaMontageData.h"
#include "../../Statics/GameplayTagContainerPair.h"
#include "SambaAbility_Montage.generated.h"

/**
 * Play a montage, listening to notifies that affect character state.
 */
UCLASS()
class SAMBA_API USambaAbility_Montage : public USambaGameplayAbility
{
	GENERATED_BODY()

public:

	// Ability activation will be blocked if any of the keys are present, UNLESS any of the value tags are present;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FGameplayTagContainerPair> ActivationBlockExceptions;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FSambaMontageData MontageData;

	protected: 
	// Optional target ASC for if we need to apply direct effects.  Usually set by trigger event data.
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* TargetComponent;

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

		/** Returns true if this ability can be activated right now. Has no side effects */
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	
protected: 
	UFUNCTION()
	void HandleMontageCompleted();
	UFUNCTION()
	void HandleMontageInterrupted();
	UFUNCTION()
	void HandleMontageCancelled();

	// Begin UObject Interface
	EDataValidationResult IsDataValid(FDataValidationContext& ValidationErrors) const override;
	// End UObject Interface
};
