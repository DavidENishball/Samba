// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "SambaCombatSettings.generated.h"

/**
 * 
 */
UCLASS(config = Combat, DefaultConfig, meta = (DisplayName = "Samba Combat Settings"))
class SAMBA_API USambaCombatSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()
	public:

	// Ability that makes the character visualize the death.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, config, Category = "Death")
	TSubclassOf<class UGameplayAbility> DefaultDeathReactionAbility;

	// Begin DeveloperSettings Interface
	FName GetCategoryName() const override;
	// End DeveloperSettings Interface
};
